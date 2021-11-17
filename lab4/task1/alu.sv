// emsys_alu : a simple ALU-like unit for the lab4 of the EmSys course 
//

module alu (
        // Inputs
	input logic [7:0] a,
	input logic [7:0] b,

	input logic [2:0] op,

        // Outputs
	output logic [7:0] q
);
// -------------------------------
	
always_comb begin
	case(op)
		3'd0: q = a + b;
		3'd1: q = a - b;
		3'd2: q = a >> b;
		3'd3: q = a << b;
		3'd4: q = a & b;
		3'd5: q = a | b;
		3'd6: q = 0;
		3'd7: q = 0;
	endcase
end

endmodule

