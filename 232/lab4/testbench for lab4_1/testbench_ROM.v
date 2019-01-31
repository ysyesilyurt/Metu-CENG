`timescale 1ns / 1ps

module testbench_ROM(
    );
	reg [3:0] romAddress; 
	wire[4:0] romData;
	integer result = 0;
	 
    FUNCROM ROM(romAddress,romData);

	initial begin
	
		$display("Starting Testbench");
		
		//sample 2 cases
		#1; 
		romAddress=4'b0000; 
		#7; 
		if (romData==5'b00000) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	

		#1; 
		
		romAddress=4'b0001; 
		#7; 
		if (romData==5'b00010) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b0010; 
		#7; 
		if (romData==5'b00100) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b0011; 
		#7; 
		if (romData==5'b00111) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		#1; 
		
		romAddress=4'b0100; 
		#7; 
		if (romData==5'b01010) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	

		#1; 
		
		romAddress=4'b0101; 
		#7; 
		if (romData==5'b01011) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		#1; 
		
		romAddress=4'b0110; 
		#7; 
		if (romData==5'b01101) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b0111; 
		#7; 
		if (romData==5'b01110) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		#1; 
		
		romAddress=4'b1000; 
		#7; 
		if (romData==5'b10001) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b1001; 
		#7; 
		if (romData==5'b10010) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b1010; 
		#7; 
		if (romData==5'b10100) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		#1; 
		
		romAddress=4'b1011; 
		#7; 
		if (romData==5'b10111) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b1100; 
		#7; 
		if (romData==5'b11001) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		#1; 
		
		romAddress=4'b1101; 
		#7; 
		if (romData==5'b11010) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		#1; 
		
		romAddress=4'b1110; 
		#7; 
		if (romData==5'b11110) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		
		
		#1; 
		
		romAddress=4'b1111; 
		#7; 
		if (romData==5'b11111) result = result + 1; 	
			else $display("time:",$time,":For romAddress:%b Error in romData:%b",romAddress,romData);	
		//fill the remaining cases...
	
		$display("Result %d",result);	
		$display("Testbench was finished");	
		$finish;
	end
	
	
endmodule