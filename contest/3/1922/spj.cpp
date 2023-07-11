#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

FILE *input, *output, *answer, *score, *message;

// 这两个函数是此次机考 SPJ 中的工具函数, 用来向评测系统汇报评测结果
// 调用这个函数，表示评测结果为 AC 并退出评测程序
void _ac (const char *msg = "") {
  fputs("1", score);
  fputs(msg, message);
  exit(0);
}

// 调用这个函数，表示评测结果为 WA 并退出评测程序
void _wa (const char *msg = "") {
  fputs("0", score);
  fputs(msg, message);
  exit(0);
}

int main (int argc, char **argv) {
  // 这些文件是 SPJ 与评测系统交互的接口, 做题时无需理会这些文件的具体含义
  // input   = fopen(argv[1], "r"); // 题目的输入文件 (这题不存在输入文件; 在 spj 中注释掉的文件打开语句一般表示此题不会用到这个文件。)
  output  = fopen(argv[2], "r"); // 用户输出 (这道题是提交答案题; 输出就是你提交的答案)
  answer  = fopen(argv[3], "r"); // 题目的答案 (1.ans 文件)
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  int totp;
  int secret;
  // 你的提交中应该包含一个数, 在这里 SPJ 会把这个数读取到 totp 变量中。
  fscanf(output, "%d", &totp);
  // 1.ans 文件中包含一个数, 在这里 SPJ 把这个数读取到 secret 变量中
  fscanf(answer, "%d", &secret);
  srand((time(NULL) / 60) ^ secret);

  int expected = rand() % 1000000;
  std::cout << expected << '\n';
  if (totp == expected) {
    // 汇报 AC 评测状态
    _ac("2FA passed.");
  } else {
    // 汇报 WA 评测状态
    _wa("Incorrect one-time password. Please try again.");
  }
}