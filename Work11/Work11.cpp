#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class edge {
public:
    edge(int i, int i1, double d) {
        start_node = i;
        end_node = i1;
        value = d;
    }

    int start_node;
    int end_node;
    double value;
};

class node {
public:
    node(int i, int j) {
        this->i = i;
        this->j = j;
    }
    int i, j;
};

double get_edge_value(int i, int j, vector<edge>& edges) {
    if (i == j)
        return 0;
    for (auto myedge : edges) {
        if ((myedge.start_node == i && myedge.end_node == j) || (myedge.end_node == i && myedge.start_node == j))
            return myedge.value;
    }
    return -1;
}

int main() {
    int n;
    vector<node> nodes;
    vector<edge> edges;
    cin >> n;
    auto* dist = new double[n];
    bool* final = new bool[n];

    for (int i = 0; i < n; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        nodes.emplace_back(p1, p2);
        dist[i] = -1;
        final[i] = false;
    }//加载节点 初始化
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int p1, p2;
        cin >> p1 >> p2;
        p1--;
        p2--;
        edges.emplace_back(p1, p2, sqrt(
            pow(nodes[p1].i - nodes[p2].i, 2)
            +
            pow(nodes[p1].j - nodes[p2].j, 2)
        ));
    }//加载边

    int snode, enode;
    cin >> snode >> enode;
    snode--;
    enode--;
    for (int i = 0; i < n; ++i) {
        dist[i] = get_edge_value(snode, i, edges);
    }

    final[snode] = true;

    for (int k = 0; k < n - 1; ++k) {
        double min = -1;
    	int min_node = -1;
        for (int i = 0; i < n; ++i) {
            if (!final[i] && ((min > dist[i] && dist[i] != -1) || min == -1)) {
                min = dist[i];
                min_node = i;
            }
        }
        if (min_node == -1)
            return -1;
        final[min_node] = true;
        for (int i = 0; i < n; ++i) {
            double v1 = get_edge_value(min_node, i, edges);
            if (v1 == -1)
                continue;
            if (!final[i] && (dist[min_node] + v1 < dist[i] || dist[i] == -1)) {
                dist[i] = dist[min_node] + v1;
            }
        }
    }

    ::printf("%0.2f", dist[enode]);

    return 0;
}
