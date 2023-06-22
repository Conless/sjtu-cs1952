/*
    Problem:
    https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1617
 
    任务：学会使用状态机解决实际问题，完成能进行简单字符串匹配的状态机。
*/

module sequence_test(
    input wire clk,
    input wire rst,
    input wire data,
    output reg flag
  );

  reg [2:0] state;
  /*
    0: xxxx
    1: xxx1
    2: xx10
    3: x101
  */

  reg suc;

  always @(posedge clk or negedge rst) begin
    if (!rst) begin
      state <= 0;
      flag <= 0;
      suc <= 0;
    end
    else begin
      case (state)
        0:
          state <= data ? 1 : 0;
        1:
          state <= data ? 1 : 2;
        2:
          state <= data ? 3 : 0;
        3: begin
          if (data) begin
            suc <= 1;
            state <= 1;
          end
          else
            state <= 2;
        end
      endcase
      if (suc) begin
        flag <= 1;
        suc <= 0;
      end
      else
        flag <= 0;
    end
  end
endmodule
