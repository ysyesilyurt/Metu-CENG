`timescale 1ns / 1ps
module FUNCROM (input [3:0] romAddress, output reg[4:0] romData);
always@(romAddress) begin
if(romAddress == 4'b0000) begin romData = 5'b00000; end
else if(romAddress == 4'b0001) begin romData = 5'b00010; end
else if(romAddress == 4'b0010) begin romData = 5'b00100; end
else if(romAddress == 4'b0011) begin romData = 5'b00111; end
else if(romAddress == 4'b0100) begin romData = 5'b01010; end
else if(romAddress == 4'b0101) begin romData = 5'b01011; end
else if(romAddress == 4'b0110) begin romData = 5'b01101; end
else if(romAddress == 4'b0111) begin romData = 5'b01110; end
else if(romAddress == 4'b1000) begin romData = 5'b10001; end
else if(romAddress == 4'b1001) begin romData = 5'b10010; end
else if(romAddress == 4'b1010) begin romData = 5'b10100; end
else if(romAddress == 4'b1011) begin romData = 5'b10111; end
else if(romAddress == 4'b1100) begin romData = 5'b11001; end
else if(romAddress == 4'b1101) begin romData = 5'b11010; end
else if(romAddress == 4'b1110) begin romData = 5'b11110; end
else if(romAddress == 4'b1111) begin romData = 5'b11111; end
end
/*Write your code here*/
endmodule
																					
module FUNCRAM (input mode,input [3:0] ramAddress, input [4:0] dataIn,input op, input [1:0] arg,  input CLK, output reg [8:0] dataOut);

reg [8:0] memo_funcram [15:0];
integer decimal_memo;
integer i;

initial 
begin
	for(i = 0; i <= 15; i = i + 1)
	begin
		memo_funcram[i] = 9'b000000000;
	end
end

always@(mode,ramAddress,dataIn,op,arg)
begin
	if(mode == 0)
	begin
		decimal_memo = ramAddress;
		dataOut = memo_funcram[decimal_memo];
	end
end

integer der0,der1,der2,der3,temp;

always@(posedge CLK)
begin
	if(mode == 1)
	begin
		decimal_memo = ramAddress;
		der0 = 0;
		der1 = 0;
		der2 = 0;
		der3 = 0;
		temp = 0;
		if(op == 1)	//derivative
		begin 
			if(arg == 2'b00) //2
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = 4*(2**3);
				der1 = 3*(2**2);
				der2 = 2*(2);
			end
			else if(arg == 2'b01) //1
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = 4;
				der1 = 3;
				der2 = 2;
			end
			else if(arg == 2'b10) //-1
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = -4;
				der1 =  3;
				der2 = -2;
			end
			else if(arg == 2'b11) //-2
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = 4*((-2)**3);
				der1 = 3*((-2)**2);
				der2 = 2*(-2);
			end
			if(dataIn[4] == 1)
			begin
				der0 = -der0;
			end
			if(dataIn[3] == 1)
			begin
				der1 = -der1;
			end
			if(dataIn[2] == 1)
			begin
				der2 = -der2;
			end
			if(dataIn[1] == 1)
			begin
				temp = der0 + der1 + der2 - 1;
				temp = (temp < 0) ? -temp : temp;
				for(i = 0; i <= 7; i = i + 1)
				begin
					memo_funcram[decimal_memo][i] = temp % 2;
					temp = temp / 2;
				end
				memo_funcram[decimal_memo][8] = (der0 + der1 + der2 - 1 < 0) ? 1 : 0;
			end
			else
			begin
				temp = der0 + der1 + der2 + 1;
				temp = (temp < 0) ? -temp : temp;
				for(i = 0; i <= 7; i = i + 1)
				begin
					memo_funcram[decimal_memo][i] = temp % 2;
					temp = temp / 2;
				end
				memo_funcram[decimal_memo][8] = (der0 + der1 + der2 + 1 < 0) ? 1 : 0;
			end
		end
		else 		//MODULO 7
		begin
			if(arg == 2'b00) //2
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = 2**4;
				der1 = 2**3;
				der2 = 2**2;
				der3 = 2;
			end
			else if(arg == 2'b01) //1
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = 1;
				der1 = 1;
				der2 = 1;
				der3 = 1;
			end
			else if(arg == 2'b10) //-1
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 =  1;
				der1 = -1;
				der2 =  1;
				der3 = -1;
			end
			else if(arg == 2'b11) //-2
			begin
				// 0 is the most significant one 
				// 1 in the last is excluded
				der0 = (-2)**4;
				der1 = (-2)**3;
				der2 = (-2)**2;
				der3 = (-2);
			end
			if(dataIn[4] == 1)
			begin
				der0 = -der0;
			end
			if(dataIn[3] == 1)
			begin
				der1 = -der1;
			end
			if(dataIn[2] == 1)
			begin
				der2 = -der2;
			end
			if(dataIn[1] == 1)
			begin
				der3 = -der3;
			end
			if(dataIn[0] == 1)
			begin
				temp = der0 + der1 + der2 + der3 - 1;
				for(i = 0; i <= 4; i = i + 1)
				begin
					if(temp > 7)
					begin
						temp = temp - 7;
					end
				end
				for(i = 0; i <= 8; i = i + 1)
				begin
					memo_funcram[decimal_memo][i] = temp % 2;
					temp = temp / 2;
				end
			end
			else
			begin
				temp = der0 + der1 + der2 + der3 + 1;
				for(i = 0; i <= 4; i = i + 1)
				begin
					if(temp > 7)
					begin
						temp = temp - 7;
					end
				end
				for(i = 0; i <= 8; i = i + 1)
				begin
					memo_funcram[decimal_memo][i] = temp % 2;
					temp = temp / 2;
				end
			end
		end
	end
end

/*Write your code here*/	
endmodule


module FUNCMEMORY(input mode, input [6:0] memInput, input CLK, output wire [8:0] result);
	/*Don't edit this module*/
	wire [4:0]  romData;

	FUNCROM RO(memInput[6:3], romData);
	FUNCRAM RA(mode, memInput[6:3], romData, memInput[2],memInput[1:0], CLK, result);

endmodule
