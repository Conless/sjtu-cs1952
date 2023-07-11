#include <utility>

const int N = 4;
class Game {
 public:
  int get (int x, int y) const {
    return matrix[x][y];
  }
  void set (char x, char y, int value) {
    matrix[x][y] = value;
  }

  enum Direction { UP, DOWN, LEFT, RIGHT };
  bool move (Direction d) {
    Game g = *this;
    if (d == UP || d == DOWN) g = g.transpose();
    if (d == DOWN || d == RIGHT) g = g.reverseRows();
    bool moved = g.moveLeft();
    if (d == DOWN || d == RIGHT) g = g.reverseRows();
    if (d == UP || d == DOWN) g = g.transpose();
    *this = g;
    return moved;
  }

  bool lost () {
    Game g = *this;
    for (Direction d : { UP, DOWN, LEFT, RIGHT }) {
      if (g.move(d)) return false;
    }
    return true;
  }

 private:
  int matrix[N][N];

  Game transpose () {
    Game g;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        g.matrix[i][j] = matrix[j][i];
      }
    }
    return g;
  }

  Game reverseRows () {
    Game g;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        g.matrix[i][j] = matrix[i][N - 1 - j];
      }
    }
    return g;
  }

  bool moveLeft () {
    bool moved = false;
    for (int i = 0; i < N; ++i) {
      // the first available empty space from L to R
      int available = 0;
      int lastValue = 0;
      int lastX = -1;
      for (int j = 0; j < N; ++j) {
        int value = matrix[i][j];
        if (!value) continue;

        // if they could be combined...
        if (value == lastValue) {
          matrix[i][j] = 0;
          matrix[i][lastX] = value + 1;
          moved = true;
          // a tile couldn't be combined twice in one move
          lastValue = 0;
        } else { // if the tiles are not combinable
          // if it is movable
          if (available != j) {
            matrix[i][j] = 0;
            matrix[i][available] = value;
            moved = true;
          }
          lastValue = value;
          lastX = available;
          ++available;
        }
      }
    }
    return moved;
  }

};
