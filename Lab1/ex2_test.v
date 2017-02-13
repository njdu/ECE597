module test;

	reg CLK,START,B0,B1,B2,B3,A0,A1,A2,A3;
	reg[32:0] count;
	wire CNTVCO2,CNTVCON2,READY,P0,P1,P2,P3,P4,P5,P6,P7;



	ex2 ex(CLK,START,B0,B1,B2,B3,A0,A1,A2,A3,CNTVCO2,CNTVCON2,READY,P0,P1,P2,P3,P4,P5,P6,P7);

	initial begin
		CLK = 0;
		ex.S0 = 0;
		ex.S1 = 0;
		ex.S2 = 0;
		ex.S3 = 0;
		ex.S4 = 0;
		ex.S5 = 0;
		ex.S6 = 0;
		ex.S7 = 0;
		ex.S8 = 0;
		ex.S9 = 0;
		ex.S10 = 0;
		ex.S11 = 0;
		ex.S12 = 0;
		ex.S13 = 0;
		ex.S14 = 0;


		count = 32'd0;

		#1000000 $display("Timed Out\n");
		#1000001 $finish;

		
	end
	

   always #0.5 CLK=~CLK; //clock toggle every 0.5 ns

   always @(posedge CLK) begin

   		count <= count + 1;

   		$display("Working");
   		if ({ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0} == 14'hFFF) begin
   			$display("%10d",count,"  state:",ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0, "  (reached target)");
   			$finish;
   		end
   		else begin
   			$display("%10d",count,"  state:",ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0);
   		end

   		START <= $random;
   		B0 <= $random;
   		B1 <= $random;
   		B2 <= $random;
   		B3 <= $random;
   		A0 <= $random;
   		A1 <= $random;
   		A2 <= $random;
   		A3 <= $random;

   end


endmodule

