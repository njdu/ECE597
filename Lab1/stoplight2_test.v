module test;

	reg CLK,Ped;
	reg[32:0] count;
	wire SigG,SigY,SigR;

	stoplight2 light(Ped, CLK, SigG,SigY,SigR);

	initial begin

		CLK = 0;
		Ped = 0;

		light.S0 = 0;
		light.S1 = 0;
		light.S2 = 0;
		light.S3 = 0;
		light.S4 = 0;

		count = 32'd0;

		#1000000 $display("Timed Out\n");
		#1000001 $finish;

		
	end
	

   always #0.5 CLK=~CLK; //clock toggle every 0.5 ns

   always @(posedge CLK) begin

   		count <= count + 1;

   		if ({light.S4,light.S3,light.S2,light.S1,light.S0} == 5'b01000) begin
   			$display("%10d",count,"  state:", light.S4, light.S3,light.S2,light.S1,light.S0, "  (reached target)");
   			$finish;
   		end
   		else begin
   			//$display("%10d", count,"  state:",light.S3,light.S2,light.S1,light.S0);
   		end

   		Ped <= $random;

   end


endmodule