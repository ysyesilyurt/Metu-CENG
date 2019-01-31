`timescale 1ns / 1ps

module testbench_ic1500;

	// Inputs
	reg a0;
	reg f0;
	reg a1;
	reg f1;
	reg clk;

	// Outputs
	wire q0;
	wire q1;
	wire y;

	// Instantiate the Unit Under Test (UUT)
	ic1500 uut (
		.a0(a0), 
		.f0(f0), 
		.a1(a1), 
		.f1(f1), 
		.clk(clk), 
		.q0(q0), 
		.q1(q1), 
		.y(y)
	);
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
	always #5 clk = ~clk;
    
	initial begin
		// set monitor to inputs and outputs
		$monitor("Time=%t | a0=%b f0=%b a1=%b f1=%b | q0=%b q1=%b", 
					$time, a0, f0, a1, f1, q0, q1);
		
		// Initialize Inputs
		a0 = 0;
		f0 = 1;
		a1 = 0;
		f1 = 1;

		// Wait 5 ns for global reset to finish
		#5;
        
		// Add stimulus here
		a0 = 0;
		f0 = 0;
		a1 = 0;
		f1 = 0;
		#10; // Wait for clock edge
		if (q0 != 1) $display("Value of q0 after a0=0 f0=0 is wrong");
		else if (q1 != 1) $display("Value of q1 after a1=0 f1=0 is wrong");
		else if (y != 0) $display("Value of y after a0=f0=a1=f1=0 is wrong");
		else $display("Successful");
	
		a0 = 1;
		f0 = 1;
		a1 = 1;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 0) $display("Value of q0 after a0=1 f0=1 is wrong");
		else if (q1 != 0) $display("Value of q1 after a1=1 f1=1 is wrong");
		else if (y != 0) $display("Value of y after a0=f0=a1=f1=1 is wrong");
		else $display("Successful");

		a0 = 1;
		f0 = 0;
		a1 = 1;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 1) $display("Value of q0 after a0=1 f0=0 is wrong");
		else if (q1 != 0) $display("Value of q1 after a1=1 f1=1 is wrong");
		else if (y != 1) $display("Value of y after f0=0 a0=a1=f1=1 is wrong");
		else $display("Successful");
		
		a0 = 1;
		f0 = 1;
		a1 = 0;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 0) $display("Value of q0 after a0=1 f0=1 is wrong");
		else if (q1 != 0) $display("Value of q1 after a1=0 f1=1 is wrong");
		else if (y != 0) $display("Value of y after a0=f0=f1=1 a1=0 is wrong");
		else $display("Successful");
		
		a0 = 1;
		f0 = 0;
		a1 = 0;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 1) $display("Value of q0 after a0=1 f0=0 is wrong");
		else if (q1 != 0) $display("Value of q1 after a1=0 f1=1 is wrong");
		else if (y != 1) $display("Value of y after a0=f1=1 a1=f0=0 is wrong");
		else $display("Successful");
		
		a0 = 1;
		f0 = 0;
		a1 = 1;
		f1 = 0;
		#10; // Wait for clock edge
		if (q0 != 1) $display("Value of q0 after a0=1 f0=0 is wrong");
		else if (q1 != 1) $display("Value of q1 after a1=1 f1=0 is wrong");
		else if (y != 0) $display("Value of y after a0=a1=1 f1=f0=0 is wrong");
		else $display("Successful");
		
		a0 = 0;
		f0 = 1;
		a1 = 0;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 1) $display("Value of q0 after a0=0 f0=1 is wrong");
		else if (q1 != 1) $display("Value of q1 after a1=0 f1=1 is wrong");
		else if (y != 0) $display("Value of y after a0=a1=1 f1=f0=1 is wrong");
		else $display("Successful");
		
		a0 = 0;
		f0 = 0;
		a1 = 1;
		f1 = 1;
		#10; // Wait for clock edge
		if (q0 != 0) $display("Value of q0 after a0=0 f0=0 is wrong");
		else if (q1 != 0) $display("Value of q1 after a1=1 f1=1 is wrong");
		else if (y != 0) $display("Value of y after a0=f0=1 a1=f1=1 is wrong");
		else $display("Successful");
		
		$finish;
	end
      
endmodule


