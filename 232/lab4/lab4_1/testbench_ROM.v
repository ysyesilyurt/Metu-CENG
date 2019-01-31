`timescale 1ns / 1ps

module testbench_RAM(
	);
	reg mode;
	reg [6:0] inp;
	wire [4:0] dataIn;
	reg CLK;
	wire [8:0] dataOut;
	integer result = 0;

	FUNCROM ROM(inp[6:3], dataIn);
	FUNCRAM RAM(mode, inp[6:3], dataIn, inp[2], inp[1:0], CLK, dataOut);

	initial begin

		$display("Starting Testbench");

		mode = 1;
		inp = 7'b0000000;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000001;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000010;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000011;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000100;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000101;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000110;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0000111;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001000;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001001;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001010;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001011;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001100;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001101;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001110;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		#3

		mode = 1;
		inp = 7'b0001111;
		CLK = 0;
		#3
		CLK = 1;
		$display("input %b in write-mode", inp);
		#3
		mode = 0;
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);
		inp = 7'b0000000; //checking whether read-mode is combinational
		#3
		$display("input %b in read-mode --> %b", inp, dataOut);

		$finish;

	end

endmodule
