#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "game.h"

struct termios orig_termios;
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

Game::Direction getDir () {
  int c;
  int state = 0;
  const char *preseq = "\x1b[";
  while (true) {
    c = getchar();
    if (c == 'q' || c == 'Q' || c == EOF) exit(0);
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

void print (const Game &g) {
  static bool clear = false;
  if (clear) printf("\x1b[%dF", N);
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

int main () {
  setbuf(stdin, NULL);
  enableRawMode();
  atexit(disableRawMode);

  while (true) {
    int x, y;
    while (true) {
      x = rand() % N;
      y = rand() % N;
      if (!g.get(x, y)) break;
    }
    g.set(x, y, 1 + rand() % 2);
    print(g);
    if (g.lost()) break;

    while (true) {
      auto d = getDir();
      bool moved = g.move(d);
      if (moved) break;
    }
  }
}
