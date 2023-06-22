/*
    Run & Think:
    Why do the values of b and sum change? 
    How is this different from the assignment in C++ and Python?
*/

module top_module();
  reg a = 0;

  wire b;
  assign b = a;

  wire[1:0] sum;
  assign sum = a + b;

  initial begin
    a = 0;
    $display("b: ", b, " sum: ", sum);
    #1
    a = 1;
    $display("b: ", b, " sum: ", sum);

  end
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, top_module);
  end
endmodule
