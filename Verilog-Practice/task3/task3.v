/*
    Problem:
    https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1618
 
    任务：掌握 Verilog 基础语法，完成一个简单的奇偶校验
*/

module odd_sel(
    input [31:0]    bus,
    input           sel,
    output          check
  );
  assign check = (^bus) ^ (!sel) ;

endmodule
