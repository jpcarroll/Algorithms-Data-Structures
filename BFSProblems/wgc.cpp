//Jack Carroll - WolfCabbageGoat Problem

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
using namespace std;

typedef int state;

map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states
map<pair<state,state>,string> edge_label;
vector <string> animals;

void initAnimals() {
  animals.push_back("wolf");
  animals.push_back("goat");
  animals.push_back("cabbage");
}

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

bool check(state s, state t) {
  if ((((s >> 0) & 1) == ((s >> 1) & 1)) && (((s >> 3) & 1) != ((s >> 1) & 1))) { return false; }
  if ((((s >> 1) & 1) == ((s >> 2) & 1)) && (((s >> 3) & 1) != ((s >> 1) & 1))) { return false; }
  if ((((t >> 0) & 1) == ((t >> 1) & 1)) && (((t >> 3) & 1) != ((t >> 1) & 1))) { return false; }
  if ((((t >> 1) & 1) == ((t >> 2) & 1)) && (((t >> 3) & 1) != ((t >> 1) & 1)))  { return false; }

  return true;
} 

void print_state(state s)
{
  cout << edge_label[make_pair(pred[s], s)] << endl;
}

void print_path(state s, state t)
{
  if (s != t) print_path(s, pred[t]);
  print_state(t);
}

bool are_neighbors(state a, state b)
{
  int count = 0;
  string edge = "";
  
  if (((a >> 3) & 1) != ((b >> 3) & 1)) {
    edge += "I crossed the river";
    count++;
  }
  else { return false; }

  for (int i = 0; i < 3; i++) {
    if (((a >> i) & 1) != ((b >> i) & 1)) {
      if (((b >> i) & 1) == ((b >> 3) & 1)) {
        edge += " with the " + animals.at(i);
        count++;
      }
      else { return false; }
    }
  }

  if (check(a, b) == false) { return false; }

  if (count <= 2) {
    edge_label[make_pair(a,b)] = edge;
    return true;
  }
  else { return false; }
}

void build_graph(void)
{

  vector<state> state;
  int s, t;
  for (int i = 0; i < 16; i++) {
    state.push_back(i);
  }

  for (int s: state) {
    for (int t: state) {
      if (are_neighbors(s, t)) {
        nbrs[s].push_back(t);
      }
    }
  }
}

int main(void)
{
  initAnimals();
  build_graph();

  state start = 0, end = 15;
  
  search (start);
  if (visited[end]) { print_path (start, end);}
  
  return 0;
}
