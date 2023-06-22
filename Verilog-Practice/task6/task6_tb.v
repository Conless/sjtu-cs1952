/*
    ans: 
    0
    0
    0
    0
    0
    1
    0
    0
    1
    0
*/

`include "task6.v"

module top_module();
  reg            clk = 1, rst = 0;
  always #5 clk = ~clk;

  reg             in = 0;
  wire            out;
  sequence_test a(
                  .data       (in),
                  .clk        (clk),
                  .rst        (rst),
                  .flag       (out)
                );

  initial begin
    #5;
    rst = 1;
    in = 1;
    #10 in = 0;
    #10 in = 1;
    #10 in = 1;
    #10 in = 0;
    #10 in = 1;
    #10 in = 1;
    #10 in = 1;
  end

  always #5 if (clk)
      $display(out);
  initial begin
    #100 $finish;
  end
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, top_module);
  end
endmodule
