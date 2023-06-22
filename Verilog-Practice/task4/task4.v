/*
    Problem:
    https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1250
 
    任务：掌握组合逻辑，完成一个加法器。
*/

module Add(
    input       [31:0]          a,
    input       [31:0]          b,
    output reg  [31:0]          sum
  );

  integer i;
  reg s = 1'b0;
  reg cin = 1'b0;
  reg cout = 1'b0;

  always @(*) begin
    for (i = 0; i < 32; i = i + 1) begin
      s = a[i] ^ b[i] ^ cin;
      cout = (a[i] & b[i]) | (a[i] & cin) | (b[i] & cin);
      cin = cout;
      sum[i] = s;
    end
  end

endmodule
