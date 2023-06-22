`include "task3_tb.v"

module led_demo_tb;
  parameter SYSCLK_PERIOD = 10;

  reg SYSCLK;
  reg NSYSRESET;

  initial begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b0;
  end

  /*iverilog */
  initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, led_demo_tb);
  end
  /*iverilog */

  initial begin
    #(SYSCLK_PERIOD * 10 )
     NSYSRESET = 1'b1;
    #1000
     $stop;
  end

  always @(SYSCLK)
    #(SYSCLK_PERIOD / 2.0) SYSCLK <= !SYSCLK;

  top_module a();

endmodule
