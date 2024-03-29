#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge &edge) const {
        return this->weight < edge.weight;
    }
};

bool edgeComparator(const Edge &first, const Edge &other) {
    return first.weight < other.weight;
}

int findRoot(int node, vector<int> &parents) {
    if (parents[node] == node) {
        return node;
    }

    parents[node] = findRoot(parents[node], parents);
    return parents[node];
}

void kruskal(vector<Edge> &edges, int nodesCount, vector<Edge> &mstEdges) {
    sort(edges.begin(), edges.end());
    vector<int> parents(nodesCount);
    for (int i = 0; i < parents.size(); ++i) {
        parents[i] = i;
    }

    for (auto const &edge : edges) {
        int fromRoot = findRoot(edge.from, parents);
        int toRoot = findRoot(edge.to, parents);
        if (fromRoot != toRoot) {
            mstEdges.push_back(edge);

            parents[fromRoot] = toRoot;
        }
    }
}

int main() {
    int nodes, edgesCount;
    cin >> nodes >> edgesCount;

    vector<Edge> edges;
    for (int i = 0; i < edgesCount; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;

        edges.push_back({from, to, weight});
    }

    vector<Edge> mstEdges;
    kruskal(edges, nodes, mstEdges);

    cout << "MST edges: " << endl;
    for (auto const &edge : mstEdges) {
        cout << edge.from << " -> " << edge.to << " with weight: " << edge.weight << endl;
    }
}
