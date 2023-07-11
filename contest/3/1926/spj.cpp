#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input, *answer, *score, *message;

void _ac (const char *msg) {
  fputs("1", score);
  fputs(msg, message);
  exit(0);
}

[[noreturn]] void _wa (const char *msg) {
  fputs("0", score);
  fputs(msg, message);
  exit(0);
}


#include "classes.h"

int main (int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  output  = fopen(argv[2], "r"); // 用户输出
  answer  = fopen(argv[3], "r"); // 题目的答案
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  create<A>()->xdAcVQ();
  _wa();
}
