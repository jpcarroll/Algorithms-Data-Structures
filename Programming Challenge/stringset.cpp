//Jack Carroll - Problem 3

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hashy for the string s in the range 0..table_size-1 */
int hashy(string s)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++) {
    h += (int) s.at(i);
  }
  return (h % 101);
}

/* Allocate a table of pointers to nodes, all initialized to NULL */
Node **allocate_table(int size)
{
  Node **table = new Node *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}

Stringset::Stringset()
{
  size = 101; // initial size of table    
  table = allocate_table(size);
  num_elems = 0; 
  count.resize(size, 0);
}

Stringset::~Stringset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
  //inserting new node
  int h = hashy(key);
  Node* temp = new Node(key, table[h]);
  table[h] = temp;
  count[h]++;
}

int Stringset::maximum(void) {
  sort(count.begin(), count.end(), greater<int>());
  int max = count[0];
  return max;
}
