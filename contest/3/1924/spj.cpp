#include <time.h>
#include <stdio.h>
#include <stdlib.h>

FILE *input, *output, *answer, *score, *message;

void _ac (const char *msg = "") {
  fputs("1", score);
  fputs(msg, message);
  exit(0);
}

void _wa (const char *msg = "") {
  fputs("0", score);
  fputs(msg, message);
  exit(0);
}

using u64 = unsigned long long;
using u128 = unsigned __int128;

// 快速幂
// pow(base, exponent, modulo) = base^exponent mod modulo
u128 pow (u128 base, int exponent, u128 modulo) {
  base %= modulo;
  u128 power = 1;
  u128 exponentRemaining = exponent;
  u128 currentPosition = 0;
  u128 currentExp2 = base;
  while (exponentRemaining > 0) {
    u128 currentDigit = exponentRemaining % 2;
    exponentRemaining >>= 1;
    if (currentDigit == 1) power = (power * currentExp2) % modulo;
    currentExp2 = (currentExp2 * currentExp2) % modulo;
  }
  return power;
}

int main (int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  output  = fopen(argv[2], "r"); // 用户输出
  answer  = fopen(argv[3], "r"); // 题目的答案
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  u64 e = 65537;
  u64 N = 11653310467824836911ull;

  u64 messageToSign = *(long long *) "LAUNCH!!";
  if (messageToSign != 2387268731397292364ull) {
    _wa("SPJ internal error. Please contact TA immediately.");
  }

  u64 sig = 4406447179838808419;
  // fscanf(output, "%llu", &sig);
  if (pow(sig, e, N) == messageToSign) _ac();
  _wa();
}
// 3180480461 3664009451