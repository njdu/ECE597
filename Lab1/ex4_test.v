module test;

	reg CLK,X,Clear,C_32,C_31,C_30,C_29,C_28,C_27,
	C_26,C_25,C_24,C_23,C_22,C_21,C_20,C_19,C_18,
	C_17,C_16,C_15,C_14,C_13,C_12,C_11,C_10,C_9,C_8,
	C_7,C_6,C_5,C_4,C_3,C_2,C_1,C_0;
	reg [32:0] count;
	wire W,Z;



	ex4 ex(CLK,X,Clear,C_32,C_31,C_30,
		C_29,C_28,C_27,C_26,C_25,C_24,
		C_23,C_22,C_21,C_20,C_19,C_18,
		C_17,C_16,C_15,C_14,C_13,C_12,
		C_11,C_10,C_9,C_8,C_7,C_6,C_5,
		C_4,C_3,C_2,C_1,C_0,W,Z);

	initial begin
		CLK = 0;
		X = 0;
		Clear = 0;

		C_0 = 0;
		C_1 = 0;
		C_2 = 0;
		C_3 = 0;
		C_4 = 0;
		C_5 = 0;
		C_6 = 0;
		C_7 = 0;
		C_8 = 0;
		C_9 = 0;
		C_10 = 0;
		C_11 = 0;
		C_12 = 0;
		C_13 = 0;
		C_14 = 0;
		C_15 = 0;
		C_16 = 0;
		C_17 = 0;
		C_18 = 0;
		C_19 = 0;
		C_20 = 0;
		C_21 = 0;
		C_22 = 0;
		C_23 = 0;
		C_24 = 0;
		C_25 = 0;
		C_26 = 0;
		C_27 = 0;
		C_28 = 0;
		C_29 = 0;
		C_30 = 0;
		C_31 = 0;

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
		ex.S15 = 0;
		ex.S16 = 0;
		ex.S17 = 0;
		ex.S18 = 0;
		ex.S19 = 0;
		ex.S20 = 0;
		ex.S21 = 0;
		ex.S22 = 0;
		ex.S23 = 0;
		ex.S24 = 0;
		ex.S25 = 0;
		ex.S26 = 0;
		ex.S27 = 0;
		ex.S28 = 0;
		ex.S29 = 0;
		ex.S30 = 0;
		ex.S31 = 0;


		count = 32'd0;

		#1000000 $display("Timed Out\n");
		#1000001 $finish;

		
	end
	

   always #0.5 CLK=~CLK; //clock toggle every 0.5 ns

   always @(posedge CLK) begin

   		count <= count + 1;

   		if ({ ex.S31, ex.S30, ex.S29, ex.S28,ex.S27,
   			ex.S26,ex.S25,ex.S24,ex.S23,ex.S22,ex.S21,
   			ex.S20,ex.S19,ex.S18,ex.S17,ex.S16,ex.S15,
   			ex.S14, ex.S13, ex.S12, ex.S11, ex.S10,
   			ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,
   			ex.S3,ex.S2,ex.S1,ex.S0} == 32'b00000000000000000000000010000000) begin
   			$display("%10d",count,"  state:", ex.S31, ex.S30, ex.S29,
   			 ex.S28,ex.S27,ex.S26,ex.S25,ex.S24,ex.S23,ex.S22,ex.S21,
   			 ex.S20,ex.S19,ex.S18,ex.S17,ex.S16,ex.S15,ex.S14, ex.S13,
   			  ex.S12, ex.S11, ex.S10, ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,
   			  ex.S4,ex.S3,ex.S2,ex.S1,ex.S0, "  (reached target)");
   			$finish;
   		end
   		else begin
   			//$display("%10d",$time,"  state:",ex.S31, ex.S30, ex.S29, ex.S28,ex.S27,ex.S26,ex.S25,ex.S24,ex.S23,ex.S22,ex.S21,ex.S20,ex.S19,ex.S18,ex.S17,ex.S16,ex.S15,ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0);
   		end

   		X <= $random;
   		Clear <= $random; 
   		C_0 <= $random;
		C_1 <= $random;
		C_2 <= $random;
		C_3 <= $random;
		C_4 <= $random;
		C_5 <= $random;
		C_6 <= $random;
		C_7 <= $random;
		C_8 <= $random;
		C_9 <= $random;
		C_10 <= $random;
		C_11 <= $random;
		C_12 <= $random;
		C_13 <= $random;
		C_14 <= $random;
		C_15 <= $random;
		C_16 <= $random;
		C_17 <= $random;
		C_18 <= $random;
		C_19 <= $random;
		C_20 <= $random;
		C_21 <= $random;
		C_22 <= $random;
		C_23 <= $random;
		C_24 <= $random;
		C_25 <= $random;
		C_26 <= $random;
		C_27 <= $random;
		C_28 <= $random;
		C_29 <= $random;
		C_30 <= $random;
		C_31 <= $random;
   end


endmodule