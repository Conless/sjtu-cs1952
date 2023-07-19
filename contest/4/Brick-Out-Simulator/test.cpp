#include <bits/stdc++.h>

using namespace std;

//
// Created by Eternal-Fir on 2023/7/18.
//

#ifndef BRICK_OUT_GAME_H
#define BRICK_OUT_GAME_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>

class Game {
 public:
  static const int k_max_n = 1e3;

  std::fstream map;

  int k, n, m, s;

  int op_cnt;
  int touch_cnt;
  int touch_zero_cnt;
  int touch_other_cnt;
  int reward;

  class Map {
   public:
    int bricks[2 * k_max_n + 1][2 * k_max_n + 1];

    Map() {
      for (int i = 0; i < 2 * k_max_n + 1; ++i) {
        for (int j = 0; j < 2 * k_max_n + 1; ++j) {
          bricks[i][j] = -1;
        }
      }
    }

    ~Map() {}

    int get_color(const int x, const int y, const int n) {
      if (x < -2 * n || x > 2 * n || y > 3 * n || y <= 0) return 10;
      if (x < -n || x > n || !x) return -1;
      if (y <= n) return -1;
      return bricks[x + n][y - n];
    }

    void set_color(const int x, const int y, const int &new_color, const int n) {
      if (x >= -n && x <= n && y > 3 * n) return;
      if (x < -n || x > n || !x) throw std::string("set_color: index out of range.");
      if (y <= n || y > 3 * n) throw std::string("set_color: index out of range.");
      if (new_color < -1 || new_color > 3) throw std::string("set_color: wrong color.");
      bricks[x + n][y - n] = new_color;
    }
  };

  inline const int get_x_direction(const int &v) {
    if (!v) return 0;
    return v < 0 ? -1 : 1;
  }

  struct Ball {
   public:
    int x, y;
    int vx, vy;
    int color_before;

    void init() {
      x = 0;
      y = 0;
      vx = 0;
      vy = -1;
      color_before = 0;
    }
  };

  struct Brick {
   public:
    int x;
    int y;
    int color = -1;
  };

  std::queue<Brick> touched_bricks;

  inline int check_op(const char &op) {
    switch (op) {
      case 'A':
        return -2;
      case 'B':
        return -1;
      case 'C':
        return 0;
      case 'D':
        return 1;
      case 'E':
        return 2;
      default:
        throw std::string("check_op: wrong option.");
    }
  }

  inline void special_reward_handler(const int &color_now) {
    if (color_now == 0) {
      touch_zero_cnt++;
    } else {
      touch_other_cnt++;
    }
    if (color_now == situation_now.ball.color_before + 1)
      situation_now.ball.color_before++;
    else
      situation_now.ball.color_before = 0;
    if (situation_now.ball.color_before == 3) {
      reward += 50;
      situation_now.ball.color_before = 0;
    }
  }

  inline const int x_left(const int &x) { return x <= 0 ? x - 1 : x; }

  inline const int x_right(const int &x) { return x >= 0 ? x + 1 : x; }

  int move(char op) {
    bool end = false;
    while (1) {
      int next_y = situation_now.ball.y + situation_now.ball.vy;
      // check y reflection
      if (next_y < 0) {  // touch the bottom
        if (!end) {
          next_y = -next_y;
          situation_now.ball.vy = -situation_now.ball.vy;
          situation_now.ball.vx += check_op(op);
          op_cnt++;
          end = true;
        } else {
          break;
        }
      }
      // check x reflection
      int x_move_length = abs(situation_now.ball.vx);
      int check_y = std::max(situation_now.ball.y, next_y);
      int check_x = situation_now.ball.x;
      if (situation_now.ball.vx) {
        bool first_step = true;
        while (x_move_length) {
          {
            if (first_step) {
              Brick A, B, C;
              if (situation_now.ball.vx > 0) {
                A.color = situation_now.map.get_color(x_right(check_x), check_y, n);
                A.x = x_right(check_x);
                A.y = check_y;
                B.color = situation_now.map.get_color(x_right(check_x) - 1, check_y, n);
                B.x = x_right(check_x) - 1;
                B.y = check_y;
                if (situation_now.ball.vy > 0) {
                  C.color = situation_now.map.get_color(x_right(check_x), check_y - 1, n);
                  C.x = x_right(check_x);
                  C.y = check_y - 1;
                } else {
                  C.color = situation_now.map.get_color(x_right(check_x), check_y + 1, n);
                  C.x = x_right(check_x);
                  C.y = check_y + 1;
                }
              } else {
                A.color = situation_now.map.get_color(x_left(check_x), check_y, n);
                A.x = x_left(check_x);
                A.y = check_y;
                B.color = situation_now.map.get_color(x_left(check_x) + 1, check_y, n);
                B.x = x_left(check_x) + 1;
                B.y = check_y;
                if (situation_now.ball.vy > 0) {
                  C.color = situation_now.map.get_color(x_left(check_x), check_y - 1, n);
                  C.x = x_left(check_x);
                  C.y = check_y - 1;
                } else {
                  C.color = situation_now.map.get_color(x_left(check_x), check_y + 1, n);
                  C.x = x_left(check_x);
                  C.y = check_y + 1;
                }
              }
              if (A.color != -1) {  // happens a reflection
                if (B.color != -1) {
                  if (C.color != -1) {  // goes back
                    if (A.color != 10) {
                      special_reward_handler(A.color);
                      situation_now.map.set_color(A.x, A.y, -1, n);
                      reward += 1;
                      touched_bricks.push(A);
                      touch_cnt++;
                    }
                    situation_now.ball.vx = -situation_now.ball.vx;
                    situation_now.ball.vy = -situation_now.ball.vy;
                  } else {
                    if (A.color != 10) {
                      special_reward_handler(A.color);
                      situation_now.map.set_color(A.x, A.y, -1, n);
                      reward += 1;
                      touched_bricks.push(A);
                      touch_cnt++;
                    }
                    situation_now.ball.vy = -situation_now.ball.vy;
                  }
                } else {
                  if (C.color != -1) {
                    if (A.color != 10) {
                      special_reward_handler(A.color);
                      situation_now.map.set_color(A.x, A.y, -1, n);
                      reward += 1;
                      touched_bricks.push(A);
                      touch_cnt++;
                    }
                    situation_now.ball.vx = -situation_now.ball.vx;
                  } else {
                    if (A.color != 10) {
                      special_reward_handler(A.color);
                      situation_now.map.set_color(A.x, A.y, -1, n);
                      reward += 1;
                      touched_bricks.push(A);
                      touch_cnt++;
                    }
                    situation_now.ball.vx = -situation_now.ball.vx;
                  }
                }
              } else {
              }
              check_x += get_x_direction(situation_now.ball.vx);
              next_y = situation_now.ball.y + situation_now.ball.vy;
              check_y = std::max(situation_now.ball.y, next_y);
            } else {  // reflect horizontal
              Brick A;
              if (situation_now.ball.vx > 0) {
                A.color = situation_now.map.get_color(x_right(check_x), check_y, n);
                A.x = x_right(check_x);
                A.y = check_y;
              } else {
                A.color = situation_now.map.get_color(x_left(check_x), check_y, n);
                A.x = x_left(check_x);
                A.y = check_y;
              }
              if (A.color != -1) {  // touch the brick
                if (A.color != 10) {
                  special_reward_handler(A.color);
                  situation_now.map.set_color(A.x, A.y, -1, n);
                  reward += 1;
                  touched_bricks.push(A);
                  touch_cnt++;
                }
                situation_now.ball.vx = -situation_now.ball.vx;
                check_x += get_x_direction(situation_now.ball.vx);
              } else {
                check_x += get_x_direction(situation_now.ball.vx);
              }
            }
          }
          first_step = false;
          x_move_length--;
        }
        situation_now.ball.x = check_x;
        situation_now.ball.y += situation_now.ball.vy;
      } else {
        check_x = x_right(situation_now.ball.x);
        Brick A;
        A.color = situation_now.map.get_color(check_x, check_y, n);
        A.x = check_x;
        A.y = check_y;
        if (A.color != -1) {
          if (A.color != 10) {
            special_reward_handler(A.color);
            situation_now.map.set_color(A.x, A.y, -1, n);
            reward += 1;
            touched_bricks.push(A);
            touch_cnt++;
          }
          situation_now.ball.vy = -situation_now.ball.vy;
        }
        situation_now.ball.y += situation_now.ball.vy;
      }
    }
    return reward;
    //        std::cout << '(' << situation_now.ball.x << ',' << situation_now.ball.y << ')' << std::endl;
    //        while (!touched_bricks.empty()) {
    //            Brick tmp = touched_bricks.front();
    //            std::cout << "brick touched: (" << tmp.x << ',' << tmp.y << ',' << tmp.color << ");\n";
    //            touched_bricks.pop();
    //        }
  }

  struct Situation {
    Ball ball;
    Map map;

    void init() { ball.init(); }

  } situation_now;

  int back_up_cnt = 0;
  std::unordered_map<int, Situation> back_up;
  std::pair<int, Situation> to_save;

 public:
  Game() {
    reward = 0;
    op_cnt = 0;
    touch_cnt = 0;
    cin >> k >> n >> m >> s;
    for (int y = 2 * n; y > 0; --y) {
      for (int x = 0; x < n; x++) cin >> situation_now.map.bricks[x][y];
      for (int x = n + 1; x <= 2 * n; ++x) cin >> situation_now.map.bricks[x][y];
    }

    //        std::cin >> k >> n >> m >> s;
    //        for (int y = 2 * n; y > 0; --y) {
    //            for (int x = 0; x < n; x++)
    //                std::cin >> bricks[x][y];
    //            for (int x = n + 1; x <= 2 * n; ++x)
    //                std::cin >> bricks[x][y];
    //        }
    situation_now.init();
  }

  int play(char op) {
    reward = 0;
    touch_cnt = 0;
    touch_zero_cnt = 0;
    touch_other_cnt = 0;
    while (!touched_bricks.empty()) touched_bricks.pop();
    return move(op);
  }

  void Print() {
    auto getChar = [](int color) { return (color == -1 || color == 10) ? ' ' : (color + '0'); };
    std::cout << '-';
    for (int x = -n; x < n; x++) std::cout << "--";
    for (int x = n + 1; x <= 3 * n; ++x) std::cout << "--";
    std::cout << '-';
    std::cout << '\n';
    for (int y = 2 * n; y > -n; --y) {
      std::cout << '|';
      for (int x = -n; x < n; x++) std::cout << char(getChar(situation_now.map.get_color(x - n, y + n, n))) << ' ';
      for (int x = n + 1; x <= 3 * n; ++x)
        std::cout << char(getChar(situation_now.map.get_color(x - n, y + n, n))) << ' ';
      std::cout << '|';
      std::cout << '\n';
    }
    std::cout << '-';
    for (int x = -n; x < n; x++) std::cout << "--";
    for (int x = n + 1; x <= 3 * n; ++x) std::cout << "--";
    std::cout << '-';
    std::cout << '\n';
  }

  int save() {
    back_up_cnt++;
    to_save.first = back_up_cnt;
    to_save.second = situation_now;
    back_up.insert(to_save);
    return back_up_cnt;
  }

  bool load(int back_up_id) {
    if (back_up.find(back_up_id) != back_up.end()) {
      situation_now = back_up.find(back_up_id)->second;
      return true;
    } else
      return false;
  }

  bool erase(int back_up_id) {
    if (back_up.find(back_up_id) != back_up.end()) {
      back_up.erase(back_up_id);
      return true;
    } else
      return false;
  }

  ~Game() {}
};

#endif  // BRICK_OUT_GAME_H

constexpr int TRY_DEPTH = 6;

Game *game;

int value;
vector<int> now, ans;

void try_play(int depth, int result, int touch) {
  if (depth == TRY_DEPTH) {
    int now_value = result - touch;
    // printf("// result = %d, touch = %d, oper = [", result, touch);
    // for (auto i : now) {
    //   printf("%c", i + 'A');
    // }
    // printf("]\n");
    if (now_value > value) {
      ans = now;
      value = now_value;
    }
    return;
  }
  int save = game->save();
  for (int i = 0; i < 5; i++) {
    now.push_back(i);
    int reward = game->play(i + 'A');
    int cur_touch = game->touch_cnt;
    // printf("// %d %d\n", reward, cur_touch);
    // printf("/*\n");
    // game->Print();
    // printf("*/\n");
    try_play(depth + 1, result + reward, touch + cur_touch);
    now.pop_back();
    game->load(save);
  }
  game->erase(save);
}

void try_bonus() {
  value = -1;
  now.clear();
  ans.clear();
  try_play(0, 0, 0);
  printf("// value = %d, oper = [", value);
  for (int i = 0; i < ans.size(); i++) {
    printf("%c", ans[i] + 'A');
  }
  printf("]\n");
  for (int i = 0; i < ans.size(); i++) {
    int result = game->play(ans[i] + 'A');
#ifdef ONLINE_JUDGE
    printf("%c\n", choice.first + 'A');
#else
    printf("puts(\"%c\"); // result = %d, touch = %d\n", ans[i] + 'A', result, game->touch_cnt);
    // printf("/*\n");
    // game->Print();
    // printf("*/\n");
#endif
  }
  fflush(stdout);
}

void output(int num) {
#ifndef ONLINE_JUDGE
  freopen(("../testcases/" + to_string(num) + ".in").c_str(), "r", stdin);
  freopen((to_string(num) + ".cpp").c_str(), "w", stdout);
  printf("#include <bits/stdc++.h>\nint main() {\n");
#endif
  game = new Game();
  for (int i = 1; i <= 10; i++) try_bonus();
  // return;
  int zero_cnt = 0;
  for (int i = 1; i <= game->m; i++) {
    int save = game->save();
    pair<int, int> choice = {0, 0};
    for (int j = 0; j < 5; j++) {
      int reward = game->play(j + 'A');
      if (reward > choice.second) {
        choice = {j, reward};
      }
      game->load(save);
    }
    game->erase(save);
    int result = game->play(choice.first + 'A');
    if (result == 0) {
      zero_cnt++;
      if (zero_cnt == 5) {
        break;
      }
      continue;
    }
#ifdef ONLINE_JUDGE
    printf("%c\n", choice.first + 'A');
#else
    // printf("%c %d\n", choice.first + 'A', result);
    printf("puts(\"%c\"); // result = %d, touch = %d\n", choice.first + 'A', result, game->touch_cnt);
    // printf("/*\n");
    // game->Print();
    // printf("*/\n");
#endif
  }
#ifndef ONLINE_JUDGE
  printf("}\n");
#endif
}

int main(int argc, char **argv) {
  output(stoi(argv[1]));
}