/*
    ans:
    1
*/

`include "task3.v"

module top_module();
  wire [31: 0]    in = 32'b101;
  wire            sel = 1'b0;
  wire            flag;
  odd_sel a(
            .bus        (in),
            .sel        (sel),
            .check      (flag)
          );

  always @(*) begin
    #1
    $display("%b", flag);
  end
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, top_module);
  end
endmodule
