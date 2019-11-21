//Jack Carroll - Problem 2

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

long long en;
long long ex;

long long answer;
long long M = 1000000;
vector<long long> v(1000001);

void init(void) {
  iota(v.begin(), v.end(), 0);
}

int compute(long long x, long long n) {
  long long nSum = ((n * (n + 1)) / 2) - x;
  long long before = (x * (x - 1)) / 2;
  if (before == (nSum - before)) { return 0; }
  else if (before > (nSum - before)) { return -1; }
  else { return 1; }
}

void check(long long n) {
  long long left = v.at(0);
  long long right = v.at(n);

  while (left <= right) {
    long long middle = (left + right) / 2;
    if (compute(middle, n) == 0) {
      en = n;
      ex = middle;
      break;
    }
    else if (compute(middle, n) == -1) {
      right = middle - 1;
    }
    else if (right - left <= 1) { break; }
    else {
      left = middle + 1;
    }
  }
}

void find(long long n) {
  for (long long i = 10; i <= M; i++) {
    check(i);
  }
}

int main(void) {

  init();

  find(M);

  answer = en + ex;

  cout << "the max of n = " << en << " and x = " << ex << " is: " << answer << endl;

  return 0;
}