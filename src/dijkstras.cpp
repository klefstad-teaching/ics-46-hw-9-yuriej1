#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
  int n = G.adjacencyList.size();

  vector<int> distance(n, INT_MAX);
  previous.resize(n, -1);
  vector<bool> visited(n, false);

  priority_queue<Node> pq;
  pq.push(Node(source, 0));
  distance[source] = 0;

  while (!pq.empty()) {
    Node current = pq.top();
    pq.pop();
    int u = current.vertex;
    if (visited[u]) continue;
    visited[u] = true;

    for (Edge & neighbor : G.adjacencyList[u]) {
      int v = neighbor.dst;
      int weight = neighbor.weight;

      if (!visited[v] && distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        previous[v] = u;
        pq.push(Node(v, distance[v]));
      }
    }
  }
  return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
  vector<int> path;
  for (int i = destination; i != -1; i = previous[i])
    path.push_back(i);
  reverse(path.begin(), path.end());
  return path;
}

void print_path(const vector<int>& v, int total) {
  len = v.size();
  for (int i = 0; i < len; ++i)
    cout << v[i] << " ";
  cout << "\nTotal cost is " << total;
}
