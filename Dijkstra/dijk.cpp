//Jack Carroll - Dijkstra's Algorithm

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <map>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

int N, M;  // number of nodes and edges
map <int, vector<int> > neighbors;         // outgoing neighbors of each node
map <pair<int,int>, double> travel_time;  // travel times of edges

int mcadams = 17731931;

void read_input(void)
{
  FILE *fp = popen ("zcat usa_network.txt.gz", "r");
  fscanf (fp, "%d %d", &N, &M);
  printf ("Reading input");
  for (int i=0; i<M; i++) {
    if (i % 1000000 == 0) { printf ("."); fflush(stdout); }
    int source, dest;
    double t;
    fscanf (fp, "%d %d %lf", &source, &dest, &t);
    neighbors[source].push_back(dest);
    travel_time[make_pair(source, dest)] = t;
  }
  fclose(fp);
  printf (" Done.\n" ); fflush(stdout); 

}

double dijkstra(int source) {
  double max = 0;

  //c[s] = 0, c[j ≠ s] = +∞
  vector<double> dis;
  for (int i = 0; i < N; i++) {
    dis.push_back(numeric_limits<double>::infinity());
  }
  dis.at(source) = 0;

  priority_queue< pair<double, int> > q;
  q.push(make_pair(0, source));

  //While Q is nonempty:
  while (!q.empty()) {

    pair<double, int> temp = q.top();
    q.pop();

    if (dis.at(temp.second) > max) { max = dis.at(temp.second); }

    int src = q.top().second;

    //For all edges (i, j) outgoing from i:
    for (int dst: neighbors[src]) {
      pair<int, int> p = make_pair(src, dst);
      //If c[i] + cost(i, j) < c[j]
      if ((dis.at(src) + travel_time[p]) < dis.at(dst)) {
        //c[j] = c[i] + cost(i, j)
        dis.at(dst) = dis.at(src) + travel_time[p];
        //pred[j] = i
        q.push(make_pair((-1 * dis.at(dst)), neighbors[src].back()));
      }
    }

  }

  return max;
}

int main(void)
{
  read_input();
  
  // The node right in front of McAdams Hall is number 17731931.
  // This should be the source when you run Dijkstra's algorithm.

  double time = dijkstra(mcadams);

  cout << "Hours of travel time: " << time << endl;
  
  return 0;
}
