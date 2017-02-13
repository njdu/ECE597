module test;

	reg CLK,Rdy1RtHS1,Rdy2RtHS1,Rdy1BmHS1,Rdy2BmHS1,InDoneHS1,RtTSHS1,
	TpArrayHS1,OutputHS1,WantBmHS1,WantRtHS1,OutAvHS1,FullOHS1,FullIHS1,
	Prog_2,Prog_1,Prog_0;
	reg[32:0] count;
	wire S26,S25,S22,S27,S14,S11,S17,
	S10,S13,S16,S6,S12,S19,S18,S15,S7,S9,S20,S28,S23,S8,S21,S24;



	ex3 ex(CLK,Rdy1RtHS1,Rdy2RtHS1,Rdy1BmHS1,Rdy2BmHS1,
		InDoneHS1,RtTSHS1,TpArrayHS1,OutputHS1,WantBmHS1,
		WantRtHS1,OutAvHS1,FullOHS1,FullIHS1,Prog_2,Prog_1,
		Prog_0,S26,S25,S22,S27,S14,S11,S17,S10,S13,S16,S6,S12,
		S19,S18,S15,S7,S9,S20,S28,S23,S8,S21,S24);

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


		count = 32'd0;

		#100 $display("Timed Out\n");
		#101 $finish;

		
	end
	

   always #0.5 CLK=~CLK; //clock toggle every 0.5 ns

   always @(posedge CLK) begin

   		count <= count + 1;

   		if ({ex.S28,ex.S27,ex.S26,ex.S25,ex.S24,ex.S23,ex.S22,ex.S21,ex.S20,ex.S19,ex.
   			S18,ex.S17,ex.S16,ex.S15,ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9,
   			 ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0} == 29'b00000000010110110000011000001) begin
   			$display("%10d",count,"  state:",ex.S28,ex.S27,ex.S26,ex.S25,
   				ex.S24,ex.S23,ex.S22,ex.S21,ex.S20,ex.S19,ex.S18,ex.S17,
   				ex.S16,ex.S15,ex.S14, ex.S13, ex.S12, ex.S11, ex.S10, ex.S9,
   				 ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0, "  (reached target)");
   			$finish;
   		end
   		else begin
   			$display("%10d",count,"  state:",ex.S14, ex.S13, ex.S12, ex.S11, ex.S10,
   			 ex.S9, ex.S8,ex.S7,ex.S6,ex.S5,ex.S4,ex.S3,ex.S2,ex.S1,ex.S0);
   		end

   		Rdy1RtHS1 <= $random;
   		Rdy2RtHS1 <= $random;
   		Rdy1BmHS1 <= $random;
   		Rdy2BmHS1 <= $random;
   		InDoneHS1 <= $random;
   		RtTSHS1 <= $random;
   		TpArrayHS1 <= $random;
   		OutputHS1 <= $random; 
   		WantBmHS1 <= $random;
   		WantRtHS1 <= $random;
   		OutAvHS1 <= $random;
   		FullOHS1 <= $random;
   		FullIHS1 <= $random;
   		Prog_2 <= $random;
   		Prog_1 <= $random;
   		Prog_0 <= $random;
   end


endmodule