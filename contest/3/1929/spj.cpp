#include <stdio.h>
#include <filesystem>

FILE *input, *output, *answer, *score, *message;

int main (int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  // output  = fopen(argv[2], "r"); // 用户输出
  // answer  = fopen(argv[3], "r"); // 题目的答案
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  // message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  // 此题仅用于测试 OJ 环境, 不计分
  fputs("0", score);
  // 将提交程序的输出复制到评测结果的消息栏
  std::filesystem::copy_file(argv[2], argv[5]);
}
