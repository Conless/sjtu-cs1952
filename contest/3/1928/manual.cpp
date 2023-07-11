#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

void print (const Game &g) {
  static bool clear = false;
  if (clear) printf("\x1b[%dF\x1b[0J", N + 1);
  clear = true;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (g.get(i, j)) {
        printf(" %5d ", 1 << g.get(i, j));
      } else {
        printf("     - ");
      }
    }
    puts("");
  }
}

Game g;
struct Move { int x, y; Game::Direction d; };
Move moves[4096];
int n = 0;

void dump () {
  for (int j = 0; j < n; ++j) {
    printf("%d %d %c\n", moves[j].x, moves[j].y, "WSAD"[moves[j].d]);
  }
  exit(0);
}

Game::Direction getDir () {
  int c;
  int state = 0;
  const char *preseq = "\x1b[";
  while (true) {
    c = getchar();
    if (c == 'q' || c == 'Q' || c == EOF) dump();
    if (state == 2) {
      if (c == 'A') return Game::UP;
      if (c == 'B') return Game::DOWN;
      if (c == 'C') return Game::RIGHT;
      if (c == 'D') return Game::LEFT;
    }
    if (c == 'w' || c == 'W' || c == 'k' || c == 'K') return Game::UP;
    if (c == 'a' || c == 'A' || c == 'h' || c == 'H') return Game::LEFT;
    if (c == 's' || c == 'S' || c == 'j' || c == 'J') return Game::DOWN;
    if (c == 'd' || c == 'D' || c == 'l' || c == 'L') return Game::RIGHT;
    if (c == preseq[state]) ++state;
    else if (c == preseq[0]) state = 1;
    else state = 0;
  }
}

int main () {
  print(g);
  for (n = 0; n < 4096; ++n) {
    int x, y;
    scanf("%d%d", &x, &y);
    auto d = getDir();
    moves[n] = { x, y, d };

    if (x >= N || y >= N) {
      printf("Index out of bound!\n");
      return 1;
    }
    int currentValue = g.get(x, y);
    // numbers are represented as exponents of two (i.e. 1 => 2, 2 => 4, 3 => 8, 4 => 16, etc.)
    // therefore, this means to set the value of the cell to 2
    g.set(x, y, std::max(currentValue, 1));
    if (g.lost()) break;

    g.move(d);
    print(g);
  }

  ++n;
  dump();
}
