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

constexpr int TRY_DEPTH = 3;

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
  // printf("// value = %d, oper = [", value);
  // for (int i = 0; i < ans.size(); i++) {
  //   printf("%c", ans[i] + 'A');
  // }
  // printf("]\n");
  for (int i = 0; i < ans.size(); i++) {
    int result = game->play(ans[i] + 'A');
    printf("%c\n", ans[i] + 'A');
  }
  // fflush(stdout);
}

void output(int num) {
#ifndef ONLINE_JUDGE
  freopen(("../testcases/" + to_string(num) + ".in").c_str(), "r", stdin);
  freopen((to_string(num) + ".cpp").c_str(), "w", stdout);
  printf("#include <bits/stdc++.h>\nint main() {\n");
#endif
  game = new Game();
  for (int i = 1; i <= 10; i++) try_bonus();
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

void go() {
  game = new Game();
  switch (game->k) {
    case 1: {
      // value = 50, oper = [CEACCD]
      puts("C");  // result = 1, touch = 1
      game->play('C');
      puts("E");  // result = 4, touch = 4
      game->play('E');
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("C");  // result = 78, touch = 78
      game->play('C');
      puts("C");  // result = 121, touch = 121
      game->play('C');
      puts("D");  // result = 85, touch = 35
      game->play('D');
      // value = 100, oper = [BAACAA]
      puts("B");  // result = 4, touch = 4
      game->play('B');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      puts("A");  // result = 20, touch = 20
      game->play('A');
      puts("C");  // result = 8, touch = 8
      game->play('C');
      puts("A");  // result = 67, touch = 17
      game->play('A');
      puts("A");  // result = 70, touch = 20
      game->play('A');
      // value = 50, oper = [ABACCC]
      puts("A");  // result = 9, touch = 9
      game->play('A');
      puts("B");  // result = 10, touch = 10
      game->play('B');
      puts("A");  // result = 7, touch = 7
      game->play('A');
      puts("C");  // result = 5, touch = 5
      game->play('C');
      puts("C");  // result = 4, touch = 4
      game->play('C');
      puts("C");  // result = 51, touch = 1
      game->play('C');
      // value = 50, oper = [CEBAAE]
      puts("C");  // result = 3, touch = 3
      game->play('C');
      puts("E");  // result = 5, touch = 5
      game->play('E');
      puts("B");  // result = 4, touch = 4
      game->play('B');
      puts("A");  // result = 2, touch = 2
      game->play('A');
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("E");  // result = 51, touch = 1
      game->play('E');
    } break;
    case 2: {
      // value = 0, oper = [AAAAAA]
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      // value = 50, oper = [ADDEAE]
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("D");  // result = 6, touch = 6
      game->play('D');
      puts("D");  // result = 1, touch = 1
      game->play('D');
      puts("E");  // result = 10, touch = 10
      game->play('E');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      puts("E");  // result = 65, touch = 15
      game->play('E');
      // value = 50, oper = [AAEADE]
      puts("A");  // result = 37, touch = 37
      game->play('A');
      puts("A");  // result = 3, touch = 3
      game->play('A');
      puts("E");  // result = 81, touch = 81
      game->play('E');
      puts("A");  // result = 8, touch = 8
      game->play('A');
      puts("D");  // result = 7, touch = 7
      game->play('D');
      puts("E");  // result = 53, touch = 3
      game->play('E');
    } break;
    case 3: {
      // value = 100, oper = [CEABAD]
      puts("C");  // result = 1, touch = 1
      game->play('C');
      puts("E");  // result = 4, touch = 4
      game->play('E');
      puts("A");  // result = 4, touch = 4
      game->play('A');
      puts("B");  // result = 8, touch = 8
      game->play('B');
      puts("A");  // result = 5, touch = 5
      game->play('A');
      puts("D");  // result = 255, touch = 155
      game->play('D');
      // value = 150, oper = [DCAACD]
      puts("D");  // result = 4, touch = 4
      game->play('D');
      puts("C");  // result = 1, touch = 1
      game->play('C');
      puts("A");  // result = 5, touch = 5
      game->play('A');
      puts("A");  // result = 1, touch = 1
      game->play('A');
      puts("C");  // result = 2, touch = 2
      game->play('C');
      puts("D");  // result = 720, touch = 570
      game->play('D');
      // value = 150, oper = [BEDABC]
      puts("B");  // result = 42, touch = 42
      game->play('B');
      puts("E");  // result = 78, touch = 78
      game->play('E');
      puts("D");  // result = 149, touch = 149
      game->play('D');
      puts("A");  // result = 40, touch = 40
      game->play('A');
      puts("B");  // result = 195, touch = 95
      game->play('B');
      puts("C");  // result = 65, touch = 15
      game->play('C');
      // value = 150, oper = [BCAEDB]
      puts("B");  // result = 59, touch = 59
      game->play('B');
      puts("C");  // result = 3, touch = 3
      game->play('C');
      puts("A");  // result = 73, touch = 23
      game->play('A');
      puts("E");  // result = 76, touch = 26
      game->play('E');
      puts("D");  // result = 12, touch = 12
      game->play('D');
      puts("B");  // result = 58, touch = 8
      game->play('B');
      // value = 50, oper = [AADDBE]
      puts("A");  // result = 34, touch = 34
      game->play('A');
      puts("A");  // result = 8, touch = 8
      game->play('A');
      puts("D");  // result = 28, touch = 28
      game->play('D');
      puts("D");  // result = 2, touch = 2
      game->play('D');
      puts("B");  // result = 30, touch = 30
      game->play('B');
      puts("E");  // result = 105, touch = 55
      game->play('E');
      // value = 100, oper = [BCAEAD]
      puts("B");  // result = 75, touch = 25
      game->play('B');
      puts("C");  // result = 23, touch = 23
      game->play('C');
      puts("A");  // result = 9, touch = 9
      game->play('A');
      puts("E");  // result = 20, touch = 20
      game->play('E');
      puts("A");  // result = 16, touch = 16
      game->play('A');
      puts("D");  // result = 63, touch = 13
      game->play('D');
    } break;
    case 4: {
      // value = 150, oper = [EACCCC]
      puts("E");  // result = 4, touch = 4
      puts("A");  // result = 400, touch = 400
      puts("C");  // result = 556, touch = 556
      puts("C");  // result = 2, touch = 2
      puts("C");  // result = 16, touch = 16
      puts("C");  // result = 3574, touch = 3424
      // value = 50, oper = [ABCDCD]
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 1, touch = 1
      puts("C");  // result = 10, touch = 10
      puts("D");  // result = 8, touch = 8
      puts("C");  // result = 8, touch = 8
      puts("D");  // result = 99, touch = 49
      // value = 100, oper = [AADCDA]
      puts("A");  // result = 14, touch = 14
      puts("A");  // result = 14, touch = 14
      puts("D");  // result = 16, touch = 16
      puts("C");  // result = 16, touch = 16
      puts("D");  // result = 34, touch = 34
      puts("A");  // result = 122, touch = 22
      // value = 100, oper = [ABCCAA]
      puts("A");  // result = 17, touch = 17
      puts("B");  // result = 33, touch = 33
      puts("C");  // result = 6, touch = 6
      puts("C");  // result = 7, touch = 7
      puts("A");  // result = 1, touch = 1
      puts("A");  // result = 415, touch = 315
      // value = 100, oper = [BACBCD]
      puts("B");  // result = 1, touch = 1
      puts("A");  // result = 6, touch = 6
      puts("C");  // result = 18, touch = 18
      puts("B");  // result = 66, touch = 66
      puts("C");  // result = 233, touch = 183
      puts("D");  // result = 398, touch = 348
      // value = 150, oper = [BDECCE]
      puts("B");  // result = 1, touch = 1
      puts("D");  // result = 14, touch = 14
      puts("E");  // result = 6, touch = 6
      puts("C");  // result = 1, touch = 1
      puts("C");  // result = 23, touch = 23
      puts("E");  // result = 657, touch = 507
      // value = 150, oper = [EAEEEB]
      puts("E");  // result = 530, touch = 530
      puts("A");  // result = 7, touch = 7
      puts("E");  // result = 12, touch = 12
      puts("E");  // result = 322, touch = 272
      puts("E");  // result = 25, touch = 25
      puts("B");  // result = 348, touch = 248
      // value = 150, oper = [DCAEDA]
      puts("D");  // result = 1, touch = 1
      puts("C");  // result = 33, touch = 33
      puts("A");  // result = 54, touch = 54
      puts("E");  // result = 12, touch = 12
      puts("D");  // result = 19, touch = 19
      puts("A");  // result = 297, touch = 147
      // value = 100, oper = [AAABDD]
      puts("A");  // result = 19, touch = 19
      puts("A");  // result = 28, touch = 28
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 63, touch = 63
      puts("D");  // result = 236, touch = 186
      puts("D");  // result = 110, touch = 60
      // value = 150, oper = [BCEADB]
      puts("B");  // result = 1, touch = 1
      puts("C");  // result = 1, touch = 1
      puts("E");  // result = 6, touch = 6
      puts("A");  // result = 130, touch = 130
      puts("D");  // result = 223, touch = 123
      puts("B");  // result = 109, touch = 59
      puts("A");  // result = 92, touch = 92
      puts("C");  // result = 43, touch = 43
      puts("C");  // result = 55, touch = 55
      puts("C");  // result = 38, touch = 38
      puts("B");  // result = 168, touch = 168
      puts("B");  // result = 48, touch = 48
      puts("D");  // result = 122, touch = 122
      puts("A");  // result = 185, touch = 185
      puts("D");  // result = 62, touch = 62
      puts("C");  // result = 179, touch = 129
      puts("C");  // result = 66, touch = 66
      puts("B");  // result = 6, touch = 6
      puts("B");  // result = 43, touch = 43
      puts("C");  // result = 161, touch = 161
      puts("C");  // result = 16, touch = 16
      puts("B");  // result = 59, touch = 59
      puts("D");  // result = 60, touch = 60
      puts("B");  // result = 13, touch = 13
      puts("D");  // result = 15, touch = 15
      puts("E");  // result = 21, touch = 21
      puts("B");  // result = 35, touch = 35
      puts("E");  // result = 50, touch = 50
      puts("B");  // result = 17, touch = 17
      puts("E");  // result = 34, touch = 34
      puts("B");  // result = 22, touch = 22
      puts("B");  // result = 20, touch = 20
      puts("B");  // result = 10, touch = 10
      puts("E");  // result = 74, touch = 24
      puts("A");  // result = 14, touch = 14
      puts("D");  // result = 11, touch = 11
      puts("A");  // result = 14, touch = 14
      puts("D");  // result = 8, touch = 8
      puts("A");  // result = 66, touch = 16
      puts("D");  // result = 11, touch = 11
      puts("C");  // result = 10, touch = 10
      puts("A");  // result = 7, touch = 7
      puts("C");  // result = 5, touch = 5
      puts("D");  // result = 15, touch = 15
      puts("E");  // result = 13, touch = 13
      puts("D");  // result = 5, touch = 5
      puts("B");  // result = 4, touch = 4
      puts("C");  // result = 6, touch = 6
      puts("D");  // result = 5, touch = 5
      puts("C");  // result = 5, touch = 5
      puts("B");  // result = 4, touch = 4
      puts("D");  // result = 6, touch = 6
      puts("E");  // result = 5, touch = 5
      puts("D");  // result = 3, touch = 3
      puts("A");  // result = 2, touch = 2
      puts("B");  // result = 52, touch = 2
      puts("D");  // result = 3, touch = 3
      puts("B");  // result = 3, touch = 3
      puts("A");  // result = 3, touch = 3
      puts("B");  // result = 4, touch = 4
      puts("B");  // result = 3, touch = 3
      puts("B");  // result = 2, touch = 2
      puts("E");  // result = 2, touch = 2
      puts("A");  // result = 1, touch = 1
      puts("A");  // result = 2, touch = 2
      puts("C");  // result = 1, touch = 1
      puts("A");  // result = 1, touch = 1
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 1, touch = 1
      puts("B");  // result = 2, touch = 2
      puts("B");  // result = 1, touch = 1
      return;
    } break;
    case 10:
    case 5: {
      // value = 1550, oper = [EACCCC]
      puts("E");  // result = 4, touch = 4
      puts("A");  // result = 1650, touch = 1600
      puts("C");  // result = 1936, touch = 1936
      puts("C");  // result = 2, touch = 2
      puts("C");  // result = 16, touch = 16
      puts("C");  // result = 51413, touch = 49913
      // value = 700, oper = [BBAEBB]
      puts("B");  // result = 1, touch = 1
      puts("B");  // result = 1853, touch = 1753
      puts("A");  // result = 8, touch = 8
      puts("E");  // result = 126, touch = 126
      puts("B");  // result = 1, touch = 1
      puts("B");  // result = 16962, touch = 16362
      // value = 200, oper = [BDCABB]
      puts("B");  // result = 18, touch = 18
      puts("D");  // result = 20, touch = 20
      puts("C");  // result = 869, touch = 719
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 14, touch = 14
      puts("B");  // result = 592, touch = 542
      // value = 150, oper = [DCEAEA]
      puts("D");  // result = 1, touch = 1
      puts("C");  // result = 14, touch = 14
      puts("E");  // result = 18, touch = 18
      puts("A");  // result = 22, touch = 22
      puts("E");  // result = 76, touch = 26
      puts("A");  // result = 288, touch = 188
      // value = 150, oper = [EBCADD]
      puts("E");  // result = 34, touch = 34
      puts("B");  // result = 1, touch = 1
      puts("C");  // result = 1, touch = 1
      puts("A");  // result = 1211, touch = 1111
      puts("D");  // result = 38, touch = 38
      puts("D");  // result = 805, touch = 755
      // value = 150, oper = [ACAEAB]
      puts("A");  // result = 1, touch = 1
      puts("C");  // result = 1, touch = 1
      puts("A");  // result = 44, touch = 44
      puts("E");  // result = 1, touch = 1
      puts("A");  // result = 330, touch = 280
      puts("B");  // result = 487, touch = 387
      // value = 250, oper = [BACDEA]
      puts("B");  // result = 43, touch = 43
      puts("A");  // result = 1, touch = 1
      puts("C");  // result = 11, touch = 11
      puts("D");  // result = 7, touch = 7
      puts("E");  // result = 1965, touch = 1815
      puts("A");  // result = 290, touch = 190
      // value = 200, oper = [AACCCA]
      puts("A");  // result = 48, touch = 48
      puts("A");  // result = 51, touch = 51
      puts("C");  // result = 1, touch = 1
      puts("C");  // result = 227, touch = 227
      puts("C");  // result = 480, touch = 480
      puts("A");  // result = 2064, touch = 1864
      // value = 250, oper = [ABCAED]
      puts("A");  // result = 53, touch = 53
      puts("B");  // result = 146, touch = 46
      puts("C");  // result = 10, touch = 10
      puts("A");  // result = 33, touch = 33
      puts("E");  // result = 1, touch = 1
      puts("D");  // result = 1934, touch = 1784
      // value = 200, oper = [ACDCAB]
      puts("A");  // result = 93, touch = 93
      puts("C");  // result = 1, touch = 1
      puts("D");  // result = 90, touch = 90
      puts("C");  // result = 3440, touch = 3340
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 275, touch = 175
      puts("C");  // result = 50, touch = 50
      puts("A");  // result = 28, touch = 28
      puts("E");  // result = 177, touch = 177
      puts("B");  // result = 748, touch = 748
      puts("C");  // result = 114, touch = 114
      puts("D");  // result = 193, touch = 193
      puts("A");  // result = 1852, touch = 1802
      puts("E");  // result = 20, touch = 20
      puts("E");  // result = 44, touch = 44
      puts("D");  // result = 19, touch = 19
      puts("E");  // result = 109, touch = 109
      puts("C");  // result = 205, touch = 205
      puts("B");  // result = 54, touch = 54
      puts("A");  // result = 178, touch = 128
      puts("B");  // result = 36, touch = 36
      puts("C");  // result = 18, touch = 18
      puts("C");  // result = 72, touch = 72
      puts("B");  // result = 75, touch = 75
      puts("E");  // result = 32, touch = 32
      puts("B");  // result = 167, touch = 167
      puts("C");  // result = 104, touch = 104
      puts("D");  // result = 940, touch = 940
      puts("B");  // result = 214, touch = 214
      puts("C");  // result = 36, touch = 36
      puts("D");  // result = 449, touch = 449
      puts("A");  // result = 16, touch = 16
      puts("A");  // result = 89, touch = 89
      puts("C");  // result = 4770, touch = 4770
      puts("A");  // result = 1620, touch = 1520
      puts("B");  // result = 324, touch = 324
      puts("C");  // result = 109, touch = 109
      puts("C");  // result = 223, touch = 223
      puts("B");  // result = 24, touch = 24
      puts("D");  // result = 137, touch = 137
      puts("B");  // result = 1541, touch = 1441
      puts("A");  // result = 1480, touch = 1480
      puts("D");  // result = 644, touch = 644
      puts("B");  // result = 151, touch = 151
      puts("E");  // result = 18, touch = 18
      puts("D");  // result = 46, touch = 46
      puts("C");  // result = 26, touch = 26
      puts("C");  // result = 137, touch = 137
      puts("E");  // result = 23, touch = 23
      puts("E");  // result = 387, touch = 287
      puts("B");  // result = 249, touch = 249
      puts("A");  // result = 60, touch = 60
      puts("E");  // result = 80, touch = 80
      puts("D");  // result = 668, touch = 668
      puts("B");  // result = 624, touch = 574
      puts("E");  // result = 96, touch = 96
      puts("D");  // result = 466, touch = 466
      puts("C");  // result = 41, touch = 41
      puts("D");  // result = 119, touch = 119
      puts("D");  // result = 68, touch = 68
      puts("A");  // result = 14, touch = 14
      puts("E");  // result = 955, touch = 905
      puts("C");  // result = 510, touch = 510
      puts("D");  // result = 62, touch = 62
      puts("A");  // result = 506, touch = 506
      puts("E");  // result = 59, touch = 59
      puts("A");  // result = 144, touch = 144
      puts("D");  // result = 80, touch = 80
      puts("C");  // result = 425, touch = 425
      puts("B");  // result = 603, touch = 603
      puts("A");  // result = 193, touch = 193
      puts("A");  // result = 388, touch = 388
      puts("E");  // result = 261, touch = 261
      puts("E");  // result = 234, touch = 234
      puts("D");  // result = 531, touch = 481
      puts("C");  // result = 43, touch = 43
      puts("B");  // result = 12, touch = 12
      puts("A");  // result = 385, touch = 385
      puts("A");  // result = 6, touch = 6
      puts("E");  // result = 38, touch = 38
      puts("B");  // result = 288, touch = 288
      puts("A");  // result = 1259, touch = 1259
      puts("D");  // result = 641, touch = 541
      puts("A");  // result = 240, touch = 240
      puts("A");  // result = 149, touch = 149
      puts("E");  // result = 2608, touch = 2408
      puts("A");  // result = 30, touch = 30
      puts("C");  // result = 131, touch = 131
      puts("A");  // result = 39, touch = 39
      puts("A");  // result = 168, touch = 168
      puts("A");  // result = 27, touch = 27
      puts("E");  // result = 318, touch = 318
      puts("E");  // result = 1185, touch = 1185
      puts("E");  // result = 282, touch = 282
      puts("D");  // result = 29, touch = 29
      puts("D");  // result = 446, touch = 446
      puts("B");  // result = 680, touch = 680
      puts("E");  // result = 89, touch = 89
      puts("C");  // result = 457, touch = 407
      puts("E");  // result = 12, touch = 12
      puts("D");  // result = 408, touch = 408
      puts("A");  // result = 521, touch = 521
      puts("E");  // result = 27, touch = 27
      puts("E");  // result = 89, touch = 89
      puts("E");  // result = 632, touch = 582
      puts("C");  // result = 410, touch = 410
      puts("E");  // result = 97, touch = 97
      puts("D");  // result = 163, touch = 163
      puts("D");  // result = 3, touch = 3
      puts("A");  // result = 46, touch = 46
      puts("A");  // result = 249, touch = 249
      puts("A");  // result = 451, touch = 451
      puts("B");  // result = 653, touch = 603
      puts("D");  // result = 353, touch = 353
      puts("B");  // result = 255, touch = 255
      puts("A");  // result = 99, touch = 99
      puts("D");  // result = 156, touch = 156
      puts("D");  // result = 708, touch = 708
      puts("D");  // result = 489, touch = 489
      puts("C");  // result = 133, touch = 133
      puts("D");  // result = 274, touch = 274
      puts("D");  // result = 157, touch = 157
      puts("E");  // result = 103, touch = 103
      puts("A");  // result = 6, touch = 6
      puts("E");  // result = 42, touch = 42
      puts("A");  // result = 194, touch = 194
      puts("C");  // result = 125, touch = 125
      puts("A");  // result = 1020, touch = 1020
      puts("E");  // result = 52, touch = 52
      puts("E");  // result = 1305, touch = 1205
      puts("A");  // result = 14, touch = 14
      puts("E");  // result = 574, touch = 574
      puts("D");  // result = 14, touch = 14
      puts("C");  // result = 110, touch = 110
      puts("B");  // result = 16, touch = 16
      puts("A");  // result = 188, touch = 188
      puts("D");  // result = 457, touch = 407
      puts("D");  // result = 16, touch = 16
      puts("A");  // result = 70, touch = 70
      puts("A");  // result = 22, touch = 22
      puts("D");  // result = 712, touch = 662
      puts("C");  // result = 1271, touch = 1271
      puts("C");  // result = 41, touch = 41
      puts("D");  // result = 279, touch = 279
      puts("E");  // result = 32, touch = 32
      puts("A");  // result = 18, touch = 18
      puts("D");  // result = 223, touch = 223
      puts("A");  // result = 469, touch = 419
      puts("E");  // result = 44, touch = 44
      puts("C");  // result = 284, touch = 284
      puts("D");  // result = 81, touch = 81
      puts("B");  // result = 247, touch = 247
      puts("C");  // result = 96, touch = 96
      puts("E");  // result = 233, touch = 233
      puts("C");  // result = 59, touch = 59
      puts("C");  // result = 22, touch = 22
      puts("D");  // result = 28, touch = 28
      puts("E");  // result = 190, touch = 140
      puts("C");  // result = 174, touch = 174
      puts("E");  // result = 150, touch = 150
      puts("B");  // result = 389, touch = 389
      puts("E");  // result = 358, touch = 358
      puts("C");  // result = 290, touch = 290
      puts("C");  // result = 221, touch = 221
      puts("E");  // result = 187, touch = 187
      puts("C");  // result = 271, touch = 271
      puts("B");  // result = 387, touch = 387
      puts("E");  // result = 98, touch = 98
      puts("A");  // result = 61, touch = 61
      puts("B");  // result = 138, touch = 138
      puts("C");  // result = 131, touch = 131
      puts("D");  // result = 58, touch = 58
      puts("E");  // result = 224, touch = 224
      puts("A");  // result = 154, touch = 154
      puts("D");  // result = 21, touch = 21
      puts("E");  // result = 15, touch = 15
      puts("C");  // result = 102, touch = 102
      puts("B");  // result = 472, touch = 422
      puts("E");  // result = 22, touch = 22
      puts("A");  // result = 54, touch = 54
      puts("E");  // result = 80, touch = 80
      puts("B");  // result = 484, touch = 484
      puts("C");  // result = 230, touch = 180
      puts("C");  // result = 216, touch = 216
      puts("D");  // result = 230, touch = 230
      puts("E");  // result = 357, touch = 357
      puts("B");  // result = 49, touch = 49
      puts("C");  // result = 307, touch = 257
      puts("C");  // result = 65, touch = 65
      puts("C");  // result = 1017, touch = 967
      puts("C");  // result = 65, touch = 65
      puts("C");  // result = 145, touch = 145
      puts("A");  // result = 78, touch = 78
      puts("C");  // result = 1039, touch = 989
      puts("E");  // result = 353, touch = 353
      puts("E");  // result = 383, touch = 383
      puts("C");  // result = 36, touch = 36
      puts("B");  // result = 28, touch = 28
      puts("E");  // result = 69, touch = 69
      puts("C");  // result = 241, touch = 241
      puts("A");  // result = 560, touch = 560
      puts("B");  // result = 192, touch = 192
      puts("A");  // result = 285, touch = 285
      puts("D");  // result = 26, touch = 26
      puts("C");  // result = 30, touch = 30
      puts("A");  // result = 60, touch = 60
      puts("D");  // result = 162, touch = 162
      puts("A");  // result = 238, touch = 238
      puts("B");  // result = 283, touch = 283
      puts("C");  // result = 242, touch = 242
      puts("D");  // result = 222, touch = 222
      puts("B");  // result = 166, touch = 166
      puts("A");  // result = 63, touch = 63
      puts("D");  // result = 16, touch = 16
      puts("B");  // result = 12, touch = 12
      puts("A");  // result = 81, touch = 81
      puts("B");  // result = 249, touch = 249
      puts("D");  // result = 14, touch = 14
      puts("A");  // result = 119, touch = 119
      puts("E");  // result = 125, touch = 125
      puts("A");  // result = 30, touch = 30
      puts("C");  // result = 117, touch = 117
      puts("B");  // result = 36, touch = 36
      puts("B");  // result = 384, touch = 384
      puts("A");  // result = 35, touch = 35
      puts("A");  // result = 324, touch = 324
      puts("E");  // result = 233, touch = 233
      puts("C");  // result = 26, touch = 26
      puts("A");  // result = 299, touch = 299
      puts("E");  // result = 186, touch = 186
      puts("E");  // result = 245, touch = 245
      puts("B");  // result = 306, touch = 306
      puts("C");  // result = 444, touch = 444
      puts("B");  // result = 16, touch = 16
      puts("C");  // result = 273, touch = 223
      puts("E");  // result = 44, touch = 44
      puts("C");  // result = 311, touch = 311
      puts("B");  // result = 99, touch = 99
      puts("C");  // result = 20, touch = 20
      puts("C");  // result = 50, touch = 50
      puts("C");  // result = 554, touch = 504
      puts("C");  // result = 21, touch = 21
      puts("D");  // result = 18, touch = 18
      puts("A");  // result = 52, touch = 52
      puts("C");  // result = 41, touch = 41
      puts("C");  // result = 428, touch = 378
      puts("E");  // result = 81, touch = 81
      puts("A");  // result = 127, touch = 127
      puts("B");  // result = 54, touch = 54
      puts("C");  // result = 132, touch = 132
      puts("B");  // result = 394, touch = 394
      puts("A");  // result = 48, touch = 48
      puts("A");  // result = 78, touch = 78
      puts("A");  // result = 80, touch = 80
      puts("A");  // result = 26, touch = 26
      puts("A");  // result = 54, touch = 54
      puts("D");  // result = 39, touch = 39
      puts("A");  // result = 325, touch = 325
      puts("B");  // result = 58, touch = 58
      puts("A");  // result = 44, touch = 44
      puts("E");  // result = 45, touch = 45
      puts("C");  // result = 77, touch = 27
      puts("B");  // result = 28, touch = 28
      puts("C");  // result = 22, touch = 22
      puts("B");  // result = 199, touch = 199
      puts("C");  // result = 191, touch = 191
      puts("D");  // result = 165, touch = 165
      puts("E");  // result = 168, touch = 168
      puts("D");  // result = 84, touch = 84
      puts("A");  // result = 25, touch = 25
      puts("D");  // result = 18, touch = 18
      puts("E");  // result = 97, touch = 97
      puts("C");  // result = 38, touch = 38
      puts("E");  // result = 104, touch = 104
      puts("C");  // result = 117, touch = 117
      puts("B");  // result = 64, touch = 64
      puts("D");  // result = 27, touch = 27
      puts("E");  // result = 170, touch = 170
      puts("D");  // result = 50, touch = 50
      puts("A");  // result = 137, touch = 137
      puts("C");  // result = 176, touch = 176
      puts("A");  // result = 220, touch = 220
      puts("E");  // result = 110, touch = 110
      puts("E");  // result = 54, touch = 54
      puts("D");  // result = 66, touch = 66
      puts("D");  // result = 100, touch = 100
      puts("C");  // result = 21, touch = 21
      puts("A");  // result = 41, touch = 41
      puts("D");  // result = 85, touch = 85
      puts("B");  // result = 46, touch = 46
      puts("C");  // result = 42, touch = 42
      puts("C");  // result = 52, touch = 52
      puts("B");  // result = 43, touch = 43
      puts("D");  // result = 47, touch = 47
      puts("D");  // result = 77, touch = 77
      puts("E");  // result = 58, touch = 58
      puts("B");  // result = 40, touch = 40
      puts("E");  // result = 64, touch = 64
      puts("B");  // result = 68, touch = 18
      puts("E");  // result = 139, touch = 139
      puts("A");  // result = 57, touch = 57
      puts("B");  // result = 29, touch = 29
      puts("A");  // result = 27, touch = 27
      puts("B");  // result = 18, touch = 18
      puts("A");  // result = 32, touch = 32
      puts("B");  // result = 69, touch = 69
      puts("A");  // result = 42, touch = 42
      puts("B");  // result = 51, touch = 51
      puts("E");  // result = 113, touch = 113
      puts("A");  // result = 45, touch = 45
      puts("C");  // result = 92, touch = 92
      puts("C");  // result = 102, touch = 102
      puts("A");  // result = 19, touch = 19
      puts("D");  // result = 99, touch = 99
      puts("A");  // result = 122, touch = 122
      puts("D");  // result = 64, touch = 64
      puts("E");  // result = 39, touch = 39
      puts("E");  // result = 46, touch = 46
      puts("E");  // result = 53, touch = 3
      puts("C");  // result = 44, touch = 44
      puts("D");  // result = 56, touch = 56
      puts("E");  // result = 20, touch = 20
      puts("B");  // result = 37, touch = 37
      puts("C");  // result = 62, touch = 12
      puts("A");  // result = 23, touch = 23
      puts("C");  // result = 13, touch = 13
      puts("B");  // result = 20, touch = 20
      puts("A");  // result = 34, touch = 34
      puts("D");  // result = 34, touch = 34
      puts("E");  // result = 38, touch = 38
      puts("C");  // result = 26, touch = 26
      puts("B");  // result = 37, touch = 37
      puts("C");  // result = 55, touch = 55
      puts("E");  // result = 27, touch = 27
      puts("B");  // result = 16, touch = 16
      puts("A");  // result = 29, touch = 29
      puts("A");  // result = 14, touch = 14
      puts("C");  // result = 14, touch = 14
      puts("C");  // result = 47, touch = 47
      puts("C");  // result = 18, touch = 18
      puts("D");  // result = 19, touch = 19
      puts("E");  // result = 24, touch = 24
      puts("C");  // result = 14, touch = 14
      puts("A");  // result = 19, touch = 19
      puts("C");  // result = 44, touch = 44
      puts("C");  // result = 33, touch = 33
      puts("C");  // result = 15, touch = 15
      puts("C");  // result = 26, touch = 26
      puts("E");  // result = 12, touch = 12
      puts("E");  // result = 11, touch = 11
      puts("C");  // result = 16, touch = 16
      puts("C");  // result = 14, touch = 14
      puts("C");  // result = 32, touch = 32
      puts("E");  // result = 17, touch = 17
      puts("C");  // result = 30, touch = 30
      puts("A");  // result = 9, touch = 9
      puts("D");  // result = 21, touch = 21
      puts("D");  // result = 10, touch = 10
      puts("D");  // result = 19, touch = 19
      puts("C");  // result = 14, touch = 14
      puts("E");  // result = 38, touch = 38
      puts("A");  // result = 33, touch = 33
      puts("A");  // result = 11, touch = 11
      puts("C");  // result = 56, touch = 6
      puts("B");  // result = 18, touch = 18
      puts("D");  // result = 16, touch = 16
      puts("B");  // result = 8, touch = 8
      puts("E");  // result = 23, touch = 23
      puts("D");  // result = 19, touch = 19
      puts("E");  // result = 24, touch = 24
      puts("E");  // result = 58, touch = 8
      puts("D");  // result = 16, touch = 16
      puts("A");  // result = 20, touch = 20
      puts("A");  // result = 16, touch = 16
      puts("A");  // result = 18, touch = 18
      puts("A");  // result = 11, touch = 11
      puts("B");  // result = 18, touch = 18
      puts("B");  // result = 14, touch = 14
      puts("A");  // result = 13, touch = 13
      puts("E");  // result = 11, touch = 11
      puts("C");  // result = 9, touch = 9
      puts("A");  // result = 14, touch = 14
      puts("A");  // result = 9, touch = 9
      puts("B");  // result = 14, touch = 14
      puts("E");  // result = 10, touch = 10
      puts("C");  // result = 9, touch = 9
      puts("E");  // result = 10, touch = 10
      puts("D");  // result = 33, touch = 33
      puts("B");  // result = 8, touch = 8
      puts("A");  // result = 14, touch = 14
      puts("D");  // result = 33, touch = 33
      puts("B");  // result = 12, touch = 12
      puts("E");  // result = 9, touch = 9
      puts("B");  // result = 23, touch = 23
      puts("E");  // result = 14, touch = 14
      puts("A");  // result = 10, touch = 10
      puts("B");  // result = 10, touch = 10
      puts("C");  // result = 14, touch = 14
      puts("A");  // result = 13, touch = 13
      puts("E");  // result = 7, touch = 7
      puts("A");  // result = 21, touch = 21
      puts("D");  // result = 75, touch = 25
      puts("D");  // result = 10, touch = 10
      puts("A");  // result = 8, touch = 8
      puts("D");  // result = 74, touch = 74
      puts("C");  // result = 13, touch = 13
      puts("E");  // result = 9, touch = 9
      puts("C");  // result = 9, touch = 9
      puts("C");  // result = 15, touch = 15
      puts("A");  // result = 6, touch = 6
      puts("A");  // result = 15, touch = 15
      puts("E");  // result = 41, touch = 41
      puts("A");  // result = 9, touch = 9
      puts("D");  // result = 10, touch = 10
      puts("A");  // result = 56, touch = 6
      puts("C");  // result = 10, touch = 10
      puts("D");  // result = 11, touch = 11
      puts("B");  // result = 9, touch = 9
      puts("C");  // result = 8, touch = 8
      puts("C");  // result = 6, touch = 6
      puts("D");  // result = 10, touch = 10
      puts("A");  // result = 27, touch = 27
      puts("A");  // result = 16, touch = 16
      puts("A");  // result = 9, touch = 9
      puts("C");  // result = 16, touch = 16
      puts("D");  // result = 10, touch = 10
      puts("D");  // result = 14, touch = 14
      puts("D");  // result = 8, touch = 8
      puts("B");  // result = 12, touch = 12
      puts("D");  // result = 14, touch = 14
      puts("D");  // result = 14, touch = 14
      puts("A");  // result = 10, touch = 10
      puts("C");  // result = 43, touch = 43
      puts("B");  // result = 12, touch = 12
      puts("A");  // result = 8, touch = 8
      puts("A");  // result = 9, touch = 9
      puts("B");  // result = 7, touch = 7
      puts("C");  // result = 21, touch = 21
      puts("E");  // result = 19, touch = 19
      puts("B");  // result = 6, touch = 6
      puts("B");  // result = 6, touch = 6
      puts("B");  // result = 18, touch = 18
      puts("C");  // result = 7, touch = 7
      puts("A");  // result = 6, touch = 6
      puts("E");  // result = 10, touch = 10
      puts("A");  // result = 7, touch = 7
      puts("A");  // result = 4, touch = 4
      puts("E");  // result = 12, touch = 12
      puts("E");  // result = 9, touch = 9
      puts("C");  // result = 6, touch = 6
      puts("A");  // result = 6, touch = 6
      puts("D");  // result = 7, touch = 7
      puts("A");  // result = 18, touch = 18
      puts("A");  // result = 7, touch = 7
      puts("A");  // result = 6, touch = 6
      puts("E");  // result = 16, touch = 16
      puts("E");  // result = 7, touch = 7
      puts("A");  // result = 10, touch = 10
      puts("A");  // result = 6, touch = 6
      puts("B");  // result = 6, touch = 6
      puts("A");  // result = 6, touch = 6
      puts("C");  // result = 13, touch = 13
      puts("A");  // result = 6, touch = 6
      puts("E");  // result = 5, touch = 5
      puts("A");  // result = 3, touch = 3
      puts("A");  // result = 4, touch = 4
      puts("B");  // result = 3, touch = 3
      puts("E");  // result = 5, touch = 5
      puts("E");  // result = 6, touch = 6
      puts("B");  // result = 3, touch = 3
      puts("A");  // result = 4, touch = 4
      puts("A");  // result = 4, touch = 4
      puts("C");  // result = 11, touch = 11
      puts("A");  // result = 6, touch = 6
      puts("D");  // result = 51, touch = 1
      puts("E");  // result = 14, touch = 14
      puts("D");  // result = 5, touch = 5
      puts("A");  // result = 4, touch = 4
      puts("B");  // result = 4, touch = 4
      puts("A");  // result = 2, touch = 2
      puts("A");  // result = 2, touch = 2
      puts("B");  // result = 3, touch = 3
      puts("E");  // result = 4, touch = 4
      puts("B");  // result = 3, touch = 3
      puts("A");  // result = 4, touch = 4
      puts("D");  // result = 10, touch = 10
      puts("C");  // result = 2, touch = 2
      puts("B");  // result = 3, touch = 3
      puts("B");  // result = 2, touch = 2
      puts("E");  // result = 1, touch = 1
      puts("D");  // result = 2, touch = 2
      puts("C");  // result = 2, touch = 2
      puts("E");  // result = 2, touch = 2
      puts("A");  // result = 2, touch = 2
      puts("D");  // result = 3, touch = 3
      puts("B");  // result = 2, touch = 2
      puts("B");  // result = 2, touch = 2
      puts("A");  // result = 1, touch = 1
      puts("B");  // result = 1, touch = 1
      puts("C");  // result = 12, touch = 12
      puts("D");  // result = 2, touch = 2
      puts("B");  // result = 1, touch = 1
      puts("A");  // result = 1, touch = 1
      return;
    } break;
    case 6:
      try_bonus();
      break;
    case 7:
      break;
    default:
      for (int i = 1; i < 5; i++) {
        try_bonus();
      }
      break;
  }
  time_t t;
  srand(time(&t));
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
      if ((game->k <= 7 && zero_cnt == 5) || (game->k > 7 && zero_cnt == 20)) {
        break;
      }
    }
    printf("%c\n", choice.first + 'A');
  }
}

int main(int argc, char **argv) {
  // output(stoi(argv[1]));
  go();
}