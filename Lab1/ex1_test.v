module test;

	reg CLK, IN;
	reg[32:0] count;
	wire OUT;



	ex1 ex(CLK, IN, OUT);

	initial begin
		CLK = 0;
		IN = 0;
		ex.S0 = 0;
		ex.S1 = 0;
		count = 32'd0;
		$display("Started up");
		//#2000000 $display("Timed Out\n");
		#2000001 $finish;	
	end
	

   always #0.5 CLK=~CLK; //clock toggle every 0.5 ns

   always @(posedge CLK) begin

   		count <= count + 1;

   		if ({ex.S1,ex.S0} == 2'b11) begin
   			$display("%8d",$time,"  state:",ex.S1,ex.S0, "  (reached target)");
   			$finish;
   		end
   		else begin
   			$display("%10d",count,"  state:",ex.S1,ex.S0);
   		end

   		IN <= $random;
   end


endmodule
