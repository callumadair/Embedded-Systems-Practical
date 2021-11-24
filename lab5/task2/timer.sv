// A memory-mapped hardware timer peripheral stub
//
// It uses the same memory-mapped interface signals as the example presented
// in Lecture 5.
//
// This video contains an overview of the interface: https://www.youtube.com/watch?v=gax3yg27doc&ab_channel=ShaneFleming

module timer (
    input logic clk,
    input logic rst,

	input logic [31:0]   addr_in, // The address for the memory mapped register
	input logic [31:0]   data_in, // incoming data 
	input logic          wr_in,   // the write signal 

	input logic          rd_in,   // the read signal
	output logic 	     rd_valid_out, // when this is high there is a valid read signal at the output
	output logic [31:0]  data_out // the output data
);
// -------------------------------

// The timer registers
logic [31:0] config_reg;
logic [31:0] lo_reg;
logic [31:0] hi_reg;
logic [31:0] loadlo_reg;
logic [31:0] loadhi_reg;

logic load_triggered;
logic update_triggered;

logic [63:0] counter;

// write interface logic
always_ff @(posedge clk) begin

        // default
        load_triggered <= 1'b0;
        update_triggered <= 1'b0;

        if ((addr_in[31:16] == 16'h3FF5) & wr_in) begin
                case(addr_in[15:0])
                        // config register write
                        16'hF000: config_reg <= data_in;

                        // Trigger a load
                        16'hF020: begin
                                load_triggered <= 1'b1;               
                        end

			// Trigger an update
			16'hF00C: begin
				update_triggered <= 1'b1;
			end
			
			16'hF018: begin
                             loadlo_reg <= data_in;
			end

			16'hF01C: begin
                             loadhi_reg <= data_in;
			end
			
                        // default -- do nothing
                        default: begin

                        end
                endcase
        end


        if (rst) begin
                config_reg <= 32'd0;
        end

end


// read interface logic
always_ff @(posedge clk) begin
        rd_valid_out <= rd_in;

        if ((addr_in[31:16] == 16'h3FF5) & rd_in) begin
                case(addr_in[15:0])
                     	// Reading the config register
                        16'hF000: begin 
                                data_out <= config_reg;
                        end

                        // default -- do nothing
                        default: begin

                        end
                endcase
        end

        if(rst) begin
                data_out <=32'd0;
                rd_valid_out <= 1'b0;
        end
end

// add or subtract
always_ff @(posedge clk) begin
	if(config_reg[31] == 1) begin
		if(config_reg[30] == 1) begin
			counter <= counter + 64'd1;
		end else if(config_reg[30] == 0) begin
			counter <= counter - 64'd1;
		end	
	end

        // Store the high and low registers into the counter
	if(load_triggered) begin
                counter[63:32] <= loadhi_reg;
		counter[31:0] <= loadlo_reg;
	end
        
        if(update_triggered) begin
                hi_reg <= counter[63:32];
                lo_reg <= counter[31:0];
        end
end

endmodule
// ----- End of MMIO interfacing module -----
