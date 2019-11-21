//Jack Carroll - Problem 1

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

vector<string> given;
vector<string> sorted;
string s;
int dist = 0;

void distance(int start) {
  if (start >= sorted.size()) { return; }
  int i = distance(sorted.begin(), find(sorted.begin(), sorted.end(), given[start]));
  int temp = i - start;
  if (temp > dist) { dist = temp; }
  distance(start + 1);
}

int main(void) {

  ifstream input("p1.txt");
  while (input >> s) {
    given.push_back(s);
    sorted.push_back(s);
  }
  input.close();

  sort(sorted.begin(), sorted.end());

  distance(0);

  cout << dist << endl;

  return 0;
}
