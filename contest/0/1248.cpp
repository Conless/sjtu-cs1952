#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#include "sort.hpp"
#else
bool query(int a, int b) { return a < b; }
#endif

std::vector<int> my_sort(int n) {
  std::vector<int> v = {0};
  for (int i = 1; i < n; ++i) {
    auto iter = upper_bound(v.begin(), v.end(), i, query);
    v.insert(iter, i);
  }
  return v;
}