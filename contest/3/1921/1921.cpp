#include <bits/stdc++.h>

using namespace std;  // NOLINT

auto main() -> int {
  string s;
  getline(cin, s);
  if (s == "gateway.army.mil login: ") {
    cout << "admin\n";
  } else {
    cout << "123456\n";
  }
  return 0;
}