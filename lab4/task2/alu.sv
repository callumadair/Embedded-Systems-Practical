// emsys_alu : a simple ALU-like unit for the lab4 of the EmSys course 
//

module alu (
	input clk,
	input rst,

    // Inputs
    	input logic [7:0] a,
	input logic [7:0] b,

	input logic [2:0] op,

    // Outputs
	output logic [7:0] q
);
// -------------------------------

reg [7:0] w;
reg [7:0] toseq;

always_ff @(posedge clk) begin
   	// Reset the register
   	if (rst) begin
      		w <= 8'd0;
	end
	else if(op == 3'd6) begin
		w <= toseq;
   	end
	else begin
		w <= q;
	end
end

always_comb begin
	case(op)
		3'd0: q = w + a;
		3'd1: q = w - a;
		3'd2: q = w >> 1;
		3'd3: q = w << 1;
		3'd4: q = w & a;
		3'd5: q = w | a;
		3'd6: begin
			toseq = a;
			q = 8'd0;	
		end
		3'd7: q = 8'd0;
	endcase
end

endmodule

