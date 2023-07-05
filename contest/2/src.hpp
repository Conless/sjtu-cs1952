#ifndef JUDGE_H
#define JUDGE_H
#include "read_support.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<vector<double>> weight[10]; // NOLINT

void Initialize() { // NOLINT
  int label = 0;
  for (auto &vec : weight) {
    for (int i = 0; i < 28; i++) {
      vec.push_back(vector<double>());
      for (int j = 0; j < 28; j++) {
        vec[i].push_back(0);
      }
    }
    label++;
  }
}

void Activate(vector<vector<double>> &image) { // NOLINT
  for (auto vec : image) {
    for (auto num : vec) {
      num = (max(num, 0.5) - 0.5) * 2;
    }
  }
}

void Normalize(vector<vector<double>> &image) { // NOLINT
  double sum = 0;
  for (auto &entry : image) {
    for (auto &num : entry) {
      sum += num * num;
    }
  }
  sum = sqrt(sum);
  for (auto &entry : image) {
    for (auto &num : entry) {
      num /= sum;
    }
  }
}

void Train(IMAGE_T &image, int correct_label) { // NOLINT
  IMAGE_T image_cp = image;
  Activate(image_cp);
  Normalize(image_cp);
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      weight[correct_label][i][j] += image_cp[i][j];
    }
  }
}

void NormalizeWeight() { // NOLINT
  for (auto &vec : weight) {
    Normalize(vec);
  }
}

auto CalcSum(IMAGE_T &image, int label) -> double { // NOLINT
  double sum = 0;
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      sum += image[i][j] * weight[label][i][j];
    }
  }
  return sum;
}

auto judge(IMAGE_T &image) -> int { // NOLINT
  double max_res = INT_MIN;
  int max_label = -1;
  IMAGE_T image_cp = image;
  Activate(image_cp);
  Normalize(image_cp);
  for (int label = 0; label < 10; label++) {
    double res = CalcSum(image_cp, label);
    if (res > max_res) {
      max_res = res;
      max_label = label;
    }
  }
  return max_label;
}

#endif