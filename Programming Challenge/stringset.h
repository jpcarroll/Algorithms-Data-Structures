//Jack Carroll - Problem 3

#ifndef STRINGSET_H /* Prevent multiple inclusion... */
#define STRINGSET_H

#include <string>
#include <vector>
using namespace std;

struct Node {
  string key;
  Node *next;
  Node(string k, Node *n) { key = k; next = n; }
  Node() { key = ""; next = NULL; }
};

class Stringset {

 private: 
  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the table
  vector<int> count;

 public:
  Stringset();
  ~Stringset();
  void insert(string key);
  int maximum(void);
};

#endif
