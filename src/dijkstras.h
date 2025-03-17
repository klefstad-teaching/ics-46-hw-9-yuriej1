#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

struct Node {
    int vertex;
    int weight;
    Node(int v = 0, int w = 0) : vertex(v), weight(w) {}
    bool operator<(const Node & other) const {
        return weight > other.weight;
    }
};

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
//    vector<vector<Edge>> adjacencyList;
    vector<int> distance;
    vector<int> previous;
    vector<bool> visited;
    Graph() : distance(), previous(), visited() {} // adjacencyList()
};

inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}

vector<int> dijkstra_shortest_path(/*const*/ Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& distance/*distances*/, const vector<int>& previous, int destination);
void print_path(const vector<int>& v, int total);
