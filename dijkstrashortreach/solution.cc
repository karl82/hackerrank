#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <bitset>
#include <array>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class Edge {
public:
    Edge(const unsigned int node, const unsigned int weight) : _node(node), _weight(weight) {}

    unsigned int node() const { return _node; }

    unsigned int weight() const { return _weight; }

    void print() const {
        // cerr << "e[" << _node << "<->" << _id2 << "](" << _weight << ")" << endl;
    };
private:
    const unsigned int _node;
    const unsigned int _weight;
};

class Node {
public:

    //Node(const Node& n) : _edges(n._edges) {}
    const vector<Edge> &edges() const { return _edges; }

    void add_edge(const Edge &e) {
        _edges.push_back(e);
        e.print();
    }

private:
    vector<Edge> _edges;
};

class Diaskra {
public:
    static Diaskra from(FILE *f) {
        unsigned int N;
        unsigned int M;

        fscanf(f, "%u %u", &N, &M);

        vector<Node> nodes(N + 1);
        unordered_set<unsigned int> edges;

        auto non_duplicates = 0;
        for (auto m = 0; m < M; m++) {
            unsigned int x, y, r;

            fscanf(f, "%u %u %u", &x, &y, &r);

            unsigned int hash = min(x, y) + (max(y, x) << 12) + (r << 24);

            if (edges.find(hash) == edges.end()) {
                edges.insert(hash);
                auto &node_x = nodes[x];
                auto &node_y = nodes[y];
                node_x.add_edge(Edge(y, r));
                node_y.add_edge(Edge(x, r));
                non_duplicates++;
            }
        }

        unsigned int S;

        fscanf(f, "%u", &S);

        cerr << "read all. non_duplicates:" << non_duplicates << " of " << M << endl;

        return Diaskra(N, S, nodes);
    }

    void calculate() {
        _unvisited_nodes.insert(_S);

        while (!_unvisited_nodes.empty()) {
            const auto shortest_node = pop_shortest_node();
            walk(shortest_node);
        }
    }

    void print_result() {
        auto pos = 0;
        for (auto n = 1; n <= _N; n++) {
            if (n == _S) {
                continue;
            }
            if (_distances[n] == numeric_limits<unsigned int>::max()) {
                cout << "-1";
            } else {
                cout << _distances[n];
            }
            cout << " ";
        }
        cout << endl;
    }

private:

    Diaskra(unsigned int N, unsigned int S, vector<Node> &nodes)
            : _N(N), _S(S), _nodes(std::move(nodes)), _distances(N + 1, numeric_limits<unsigned int>::max()),
              _visited_nodes(_N + 1) {
        _distances[_S] = 0;
        unsigned int n = 0;
    }

    void walk(unsigned int node) {
        if (_visited_nodes[node] == 1) {
            // cerr << "node " << target_node << " already in path!" << endl;
            return;
        }

        const auto current_distance = _distances[node];

        _visited_nodes[node] = 1;
        for (const auto &e : _nodes[node].edges()) {
            const auto tentative_distance = e.weight() + current_distance;
            if (tentative_distance < _distances[e.node()]) {
                _distances[e.node()] = tentative_distance;
                _unvisited_nodes.insert(e.node());
            }
        }
    }

    unsigned int pop_shortest_node() {
        unsigned int shortest_node = _S;
        auto min_distance = numeric_limits<unsigned int>::max();
        for (auto node : _unvisited_nodes) {
            if (_distances[node] < min_distance) {
                shortest_node = node;
                min_distance = _distances[node];
            }
        }

        _unvisited_nodes.erase(shortest_node);

        return shortest_node;
    }

    const unsigned int _N;
    const unsigned int _S;
    const vector<Node> _nodes;
    vector<unsigned int> _distances;
    vector<unsigned int> _visited_nodes;
    unordered_set<unsigned int> _unvisited_nodes;
};

int main(int argc, char **args) {
    FILE *f = argc > 1 ? fopen(args[1], "r") : stdin;
    unsigned int T;
    fscanf(f, "%u", &T);

    for (auto t = 0; t < T; t++) {
        Diaskra d = Diaskra::from(f);
        d.calculate();
        d.print_result();
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}

