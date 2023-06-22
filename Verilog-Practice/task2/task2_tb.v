
/*
    Run & Think:
    Why do the output values of a, b, c like this? 
    How is this different from the assignment in C++ and Python?
*/

module top_module();
  reg            clk = 0;
  always #5 clk = ~clk;

  reg [1:0]      a = 1;
  reg [1:0]      b = 2;
  reg [1:0]      c = 3;
  always @(posedge clk) begin
    a <= b;
    b <= c;
    c <= a;
  end

  initial
    $monitor("a = %h, b = %h, c = %h", a, b, c);
  initial begin
    #30 $finish;
  end
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, top_module);
  end
endmodule
