// Busses and Muxes Testbench
//
// author: stf

module top_tb(
    input clk,
    input rst,

    input logic [7:0] a_in,
    input logic [7:0] b_in,
    input logic [2:0] op_in,

    output logic [7:0] q_out
);

   alu alu_inst(
	// inputs
        .a(a_in),
        .b(b_in),
        .op(op_in),
	
	// outputs
        .q(q_out)
   );

   always_ff @(posedge clk) begin 
        $display("opcode=%b, a=%d, b=%d, q=%d ", op_in, a_in, b_in, q_out);
   end


   // Print some stuff as an example
   initial begin
      if ($test$plusargs("trace") != 0) begin
         $display("[%0t] Tracing to logs/vlt_dump.vcd...\n", $time);
         $dumpfile("logs/vlt_dump.vcd");
         $dumpvars();
      end
      $display("[%0t] Model running...\n", $time);
   end

endmodule
