`timescale 1ns / 1ps

module af(
    input a,
    input f,
    input clk,
    output reg q
    );
    
    initial begin
        q = 0;
    end
	
    // write your code here
    
	 always @(posedge clk) begin
    case({a,f})
      2'b0_0 : q <= ~q;
      2'b0_1 : q <=  q;
      2'b1_0 : q <=  1;
      2'b1_1 : q <=  0;
    endcase
  end

endmodule


module ic1500(
    input a0, 
    input f0, 
    input a1, 
    input f1, 
    input clk, 
    output q0, 
    output q1, 
    output y
    );

    // write your code here
	 
	 af ff1(a0,f0,clk,q0);
	 af ff2(a1,f1,clk,q1);
	 
	 assign y = q0 ^ q1;
	
endmodule
