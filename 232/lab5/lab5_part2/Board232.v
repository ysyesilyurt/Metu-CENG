`timescale 1ns / 1ps

module Board232 (
	input mclk,
	input [3:0] btn,
	input [7:0] sw,
	output [7:0] led,
	output reg [6:0] seg,
	output reg [3:0] an,
	output dp,
	output [2:1] OutBlue,
	output [2:0] OutGreen,
	output [2:0] OutRed,
	output HS,
	output VS
    );
    assign dp = 1'b1;
	 assign led[5:4]=2'b00;
	 
	 initial begin
		  seg[6:0] = 7'b0111111;
        an[3:0]  = 4'b0000; // 7 segmentte hangi yerler yanacak
        
	 end
 
 
    // adjust board clock
   reg [26:0] mclk_counter;
	initial mclk_counter<= 0;
	always @(posedge mclk) mclk_counter = mclk_counter+1;
	 // select clock : 26->slower | 24->faster
   reg clk;
   initial clk = 1'b0;
  always@(btn[3] or mclk_counter[25] or btn[0]) 
    begin
        if(btn[3]) 
            clk = mclk_counter[25];
        else 
            clk = btn[0];
    end

	reg[3:0]  seg_digits;
	wire[3:0] currentFloor1;
	wire[3:0] currentFloor2;
	wire doorOpen1;
	wire doorOpen2;

	Elevator elv (clk,
				sw[7:6], //2-bit mod selector
				sw[3:0], //4-bit elevator call request
				currentFloor1[3:0], //to be used to show in 1st 7-segment display
				currentFloor2[3:0], //to be used to show in 3rd 7-segment display
				doorOpen1, //to be used to show in 2nd 7-segment display
				doorOpen2, //to be used to show in 4th 7-segment display
				led[3:0], //to list the 4-bit requests in list mode
				led[6], //listBusy LED
				led[7] //OFF -> IDLE state, ON -> WORK state
				);
				
 always @(mclk_counter[18:17])
	begin
		
			case (mclk_counter[18:17])
				2'b00:
					begin
						an = 4'b1110;
						seg_digits = currentFloor1[3:0];
					end
				2'b01:
					begin
						an = 4'b1101;
						seg_digits = doorOpen1;
					end
				2'b10:
					begin
						an = 4'b1011;
						seg_digits = currentFloor2[3:0];
					end
				2'b11:
					begin
						an = 4'b0111;
						seg_digits = doorOpen2;
					end
				default:
					begin
						an = 4'b1111;
					end
			endcase
		

		case (seg_digits)
			4'd0: seg <= ~7'h3F;
			4'd1: seg <= ~7'h06;
			4'd2: seg <= ~7'h5B;
			4'd3: seg <= ~7'h4F;
			4'd4: seg <= ~7'h66;
			4'd5: seg <= ~7'h6D;
			4'd6: seg <= ~7'h7D;
			4'd7: seg <= ~7'h07;
			4'd8: seg <= ~7'h7F;
			4'd9: seg <= ~7'h6F;
			4'd10: seg <= ~7'h77;
			4'd11: seg <= ~7'h7C;
			4'd12: seg <= ~7'h39;
			4'd13: seg <= ~7'h5E;
			4'd14: seg <= ~7'h79;
			4'd15: seg <= ~7'h71;
			default: seg <= ~7'b1000000;
		endcase
		
	end
	
	// VGA
	assign OutBlue = 0;
	assign OutGreen = 0;
	assign OutRed = 0;
	assign HS = 0;
	assign VS = 0;

endmodule