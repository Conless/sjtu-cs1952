#include <iostream>
#include "game.h"

int main() {
  Game *game = new Game();
  while (1) {
    int choice;
    int id;
    bool result;
    int reward;
    char op;
    std::cin >> op;
    reward = game->play(op);
    game->Print();
    std::cout << reward << std::endl;
  }
  delete (game);

  return 0;
}