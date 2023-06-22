/*
    ans:
    0
    0
    0
    1
    0
*/

`include "task5.v"

module top_module();
  reg            clk = 1, rst = 0;
  always #5 clk = ~clk;

  reg             in = 0;
  wire            out;
  seq_circuit a(
                .C          (in),
                .clk        (clk),
                .rst        (rst),
                .Y          (out)
              );

  initial begin
    #5 rst = 1;
    #10 in = 1;
    #10 in = 0;
    #10 in = 1;
    #10 in = 0;
  end

  always #5 if (clk)
      $display(out);
  initial begin
    #50 $finish;
  end
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, top_module);
  end
endmodule
