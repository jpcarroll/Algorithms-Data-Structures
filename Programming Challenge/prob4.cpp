//Jack Carroll - Problem 4

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

unordered_set<int> seen;
vector<int> nodes;
int maxJumps = 0;

void insert(void) {

    int val;
    nodes.push_back(0);
    ifstream input("p4.txt");
    while (input >> val) {
        nodes.push_back(val);
    }
    input.close();
}

int compute(int line, int x) {
    int jumps = 1;
    while(line != x) {
        seen.insert(x);
        jumps++;
        x = nodes[x];
        if(seen.find(x) != seen.end()) { break; }
    }
    return jumps;
}

void find(void) {
    for (int i = 1; i < nodes.size() - 1; i++) {
        int x = nodes[i];
        int temp = compute(i, x);
        if (temp > maxJumps) { maxJumps = temp; }
    }
}

int main(void) {

    insert();
    find();

    cout << "max jumps: " << maxJumps << endl;

    return 0;
}