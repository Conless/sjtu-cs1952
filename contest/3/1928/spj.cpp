#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "game.h"

FILE *input, *output, *answer, *score, *message;

void _ac(const char *msg = "") {
  fputs("1", score);
  fputs(msg, message);
  exit(0);
}

[[noreturn]] void _wa(const char *msg = "") {
  fputs("0", score);
  fputs(msg, message);
  exit(0);
}

const int M = 4096;
Game g[M];
int n;

void print() {
  printf("   %5d  %5d  %5d  %5d\n", 0, 1, 2, 3);
  for (int i = 0; i < 4; ++i) {
    printf("%d ", i);
    for (int j = 0; j < 4; ++j) {
      if (g[n].get(i, j)) {
        printf(" %5d ", 1 << g[n].get(i, j));
      } else {
        printf("     - ");
      }
    }
    printf("\n");
  }
}

[[noreturn]] void calcScore() {
  int max = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      max = std::max(max, g[n].get(i, j));
    }
  }
  print();
  if (max >= 17) _ac();
  double s = 1.0 / (1 << (17 - max));
  fprintf(score, "%lf\n", s);
  exit(0);
}

Game::Direction getDir() {
  char c;
  while (true) {
    scanf("%c", &c);
    if (c == 'q' || c == 'Q' || c == EOF) calcScore();
    if (c == 'w' || c == 'W' || c == 'k' || c == 'K') return Game::UP;
    if (c == 'a' || c == 'A' || c == 'h' || c == 'H') return Game::LEFT;
    if (c == 's' || c == 'S' || c == 'j' || c == 'J') return Game::DOWN;
    if (c == 'd' || c == 'D' || c == 'l' || c == 'L') return Game::RIGHT;
  }
}

int main(int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  output = fopen(argv[2], "r");  // 用户输出
  // answer  = fopen(argv[3], "r"); // 题目的答案
  score = fopen(argv[4], "w");    // 把评测的分数输出到这里
  message = fopen(argv[5], "w");  // 这里输出错误/提示信息

  for (n = 0; n < M; ++n) {
    if (n > 0) g[n] = g[n - 1];

    int x, y;
    scanf("%d%d", &x, &y);
    fprintf(message, "%d %d ", x, y);
    auto d = getDir();
    if (d == Game::UP) {
      fprintf(message, "w\n");
    }
    if (d == Game::DOWN) {
      fprintf(message, "s\n");
    }
    if (d == Game::LEFT) {
      fprintf(message, "a\n");
    }
    if (d == Game::RIGHT) {
      fprintf(message, "d\n");
    }

    if (x >= 4 || y >= 4) _wa("Index out of bound");
    int currentValue = g[n].get(x, y);
    // numbers are represented as exponents of two (i.e. 1 => 2, 2 => 4, 3 => 8, 4 => 16, etc.)
    // therefore, this means to set the value of the cell to 2
    g[n].set(x, y, std::max(currentValue, 1));
    if (g[n].lost()) break;

    g[n].move(d);
    print();
  }

  calcScore();
}
