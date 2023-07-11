#include <bits/stdc++.h>
#include <climits>

using namespace std; // NOLINT

int main() {  // NOLINT
  for (unsigned int i = 28107245; i <= 28150445; i++) {
    srand(i);
    int secret = rand();
    srand(i ^ secret);
    if (rand() % 1000000 == 149124) {
      cout << i << endl;
    }
  }
  return 0;
}