#include "read_support.hpp"
#include "src.hpp"
#include <assert.h>
#include <cstdio>
#include <filesystem>
#include <fstream>

using namespace std::filesystem;
using namespace std;
// #define OJ
int main(int argc, char **argv) {
#ifndef OJ
  int cnt, correct_cnt;
  cnt = correct_cnt = 0;
  assert(argc <= 2);
  if (argc == 1) {
    // {
    //   Initialize();
    //   path pt = path("./data");
    //   // walk through all subdirectories
    //   directory_iterator itr(pt);
    //   for (auto &it : itr) {
    //     for (auto &it2 : directory_iterator(it.path())) {
    //       cout << "opening " << (it2).path().relative_path() << endl;
    //       IMAGE_T image = read_ppm(it2.path().string());
    //       int correct_label = stoi(it.path().filename().string());
    //       Train(image, correct_label);
    //     }
    //   }
    //   NormalizeWeight();
    // }
    {
      path pt = path("./data");
      // walk through all subdirectories
      directory_iterator itr(pt);
      for (auto &it : itr) {
        for (auto &it2 : directory_iterator(it.path())) {
          cout << "opening " << (it2).path().relative_path();
          IMAGE_T image = read_ppm(it2.path().string());
          int correct_label = stoi(it.path().filename().string());
          int label = judge(image);
          if (label == correct_label) {
            correct_cnt++;
            cout << " correct" << endl;
          } else {
            cout << " wrongly labled as " << label << endl;
          }
          cnt++;
        }
      }
      Output();
    }
  } else {
    std::string label_s = argv[1];
    int label_i = stoi(label_s);
    path pt = path("./data") / path(label_s);
    if (!exists(pt) || !is_directory(pt)) {
      cout << pt.relative_path() << ":path not exists or not a directory"
           << endl;
      return 0;
    }
    directory_iterator itr(pt);
    for (auto &it : itr) {
      cout << "opening " << it.path().filename() << endl;
      IMAGE_T image = read_ppm(it.path().string());
      int label = judge(image);
      if (label_i == label) {
        correct_cnt++;
      }
      cnt++;
    }
  }
  // printf("correct rate: %d/%d\n", correct_cnt, cnt);
#else
  // read from stdin
  int label;
  int cnt, correct_cnt;
  cnt = correct_cnt = 0;
  IMAGE_T image;
  // read until EOF
  while (cin >> label) {
    image = read_ppm();
    check(image);
    int label_j = judge(image);
    if (label_j == label) {
      correct_cnt++;
    }
    cnt++;
  }
  printf("correct rate: %d/%d\n", correct_cnt, cnt);
#endif
  return 0;
}