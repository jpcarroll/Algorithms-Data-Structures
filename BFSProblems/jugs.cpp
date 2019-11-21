//Jack Carroll - Fill 2 Jugs Problem

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
using namespace std;

typedef pair<int,int> state;

map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states
map<pair<state,state>,string> edge_label;

void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

void print_state(state s)
{
  if (!((s.first) == 0) || !((s.second) == 0)) {
    cout << edge_label[make_pair(pred[s], s)];
  }
  cout << "a = " << s.first << " & b = " << s.second << endl;
}

void print_path(state s, state t)
{
  if (s != t) print_path(s, pred[t]);
  print_state(t);
}

bool are_neighbors(string a, string b)
{
  int count = 0;
  for (int i=0; i<5; i++)
    if (a[i] != b[i]) count++;
  return count==1;
}

void edge(int a, int b, int c, int d, string label) {
  state j = make_pair(a, b);
  state i = make_pair(c, d);
  nbrs[j].push_back(i);
  edge_label[make_pair(j, i)] = label;
}

void build_graph(void)
{

  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 4; j++) {
      
      edge(i, j, 3, j, "Fill 1\n");
      edge(i, j, i, 4, "Fill 2\n");
      edge(i, j, 0, j, "Empty 1\n");
      edge(i, j, i, 0, "Empty 2\n");

      int min1 = min(i, 4-j);
      edge(i, j, i - min1, j + min1, "Checking for overflow for Jug 2\n");

      int min2 = min(3 - i, j);
      edge(i, j, i + min2, j - min2, "Checking for overflow for Jug 1\n");

    }
  }

}

int main(void)
{
  build_graph();

  state start = make_pair(0, 0), end;
  
  search (start);
  for (int i = 0; i < 4; i++) {
    end = make_pair(i, 5 - i);
    if (visited[end]) {
      print_path (start, end);
      cout << endl;
      break;
    }
  }
  
  return 0;
}
