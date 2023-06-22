/*
    Problem:
    https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1616
 
    任务：掌握时序逻辑，了解状态机，完成给定状态转移图对应的状态机。
 
    PS：下方的代码注释仅为建议，可以使用任意方式解决问题（以下代码均可以改动）。
*/

module seq_circuit(
    input           C,
    input           clk,
    input           rst,
    output wire     Y
  );
  reg [1:0] now_state, next_state;
  reg tag = 0;

  always @(posedge clk or negedge rst) begin
    now_state <= rst ? next_state : 2'b00;
  end

  always @ (*) begin
    if (now_state == 2'b00) begin
      next_state <= C ? 2'b01 : 2'b00;
    end
    if (now_state == 2'b01) begin
      next_state <= C ? 2'b01 : 2'b11;
    end
    if (now_state == 2'b10) begin
      next_state <= C ? 2'b10 : 2'b00;
    end
    if (now_state == 2'b11) begin
      next_state <= C ? 2'b10 : 2'b11;
    end
  end

  assign Y = (next_state >> 1 & 1) & (now_state >> 1 & 1);

endmodule
