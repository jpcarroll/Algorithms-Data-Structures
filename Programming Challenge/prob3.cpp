//Jack Carroll - Problem 3

#include <iostream>
#include <fstream>
#include <string.h>
#include <unordered_set>
#include "stringset.h"

using namespace std;

Stringset S;
unordered_set<string> ss;

void insert(void) {

    string word;

    ifstream input("p3.txt");
    while (input >> word) {
        ss.insert(word);
    }
    input.close();

    for (const auto& elem: ss) {
        S.insert(elem);
    }

}

int main(void) {

    insert();

    int max = S.maximum();

    cout << "Max fullness of bucket is " << max << endl;

    return 0;
}