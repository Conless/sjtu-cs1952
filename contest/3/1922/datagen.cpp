#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main () {
  srand(28147801);
  FILE *f = fopen("1.ans", "w");
  int secret = rand();
  fprintf(f, "%d\n", secret);
  fclose(f);
  cout << secret << endl;

  srand(28147801 ^ secret);
  f = fopen("log.txt", "w");
  int res = rand() % 1000000;
  fprintf(f, "Please confirm your TOTP now is %06d.\n", res);
  cout << res << endl;

  srand(28147802 ^ secret);
  res = rand() % 1000000;
  fprintf(f, "Please confirm your TOTP now is %06d.\n", res);
  cout << res << endl;

  srand(28147803 ^ secret);
  res = rand() % 1000000;
  fprintf(f, "Please confirm your TOTP now is %06d.\n", res);
  cout << res  << endl;

  return 0;
}
