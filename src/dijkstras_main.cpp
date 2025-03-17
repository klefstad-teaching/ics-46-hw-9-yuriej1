#include "dijkstras.h"

using namespace std;

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);
    int source = 0;
    int destination = G.numVertices - 1;

    vector<int> previous(G.numVertices);
    vector<int> distance = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distance, previous, destination);

    int total = distance[destination];
    print_path(path, total);
    return 0;
}
