#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <climits>
#include <limits>
#include <utility>

using namespace std;

using ll = long long;
using ld = long double;
using size_t = std::size_t;

using Edge = pair<char, ld>; // {neighbor, cost}
using State = pair<char, ld>; // {node, heuristic}

constexpr ld INF = numeric_limits<ld>::max() / 2.0;

struct BestResult{
    vector<char> path;
    ld cost;
};

vector<char> path_tracking(const vector<char>& parent, char goal, ld cost){
    vector<char> path;

    if(cost == INF) return {};

    for(char v = goal; v != static_cast<char>(-1); v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    return path;
}

BestResult GBFS(const vector<vector<Edge>>& graph, const vector<ld>& heuristic, char start, char goal){
    size_t n = graph.size();

    if(n == 0) throw invalid_argument("Empty graph");
    if(start >= n || goal >= n) throw out_of_range("Invalid start or goal vertex");

    ld cost_edge = 0;

    priority_queue<State, vector<State>, greater<State>> pq;
    vector<char> parent(n, static_cast<char>(-1));

    pq.push({start, heuristic[start]});

    while(!pq.empty()){
        auto [curr_node, curr_heur] = pq.top();
        pq.pop();

        if(curr_node == goal) return BestResult{path_tracking(parent, goal, cost_edge), cost_edge};

        for(const auto& [neighbor, cost] : graph[curr_node]){
            pq.push({neighbor, heuristic[neighbor]});
            parent[neighbor] = curr_node;
            cost_edge += cost;
        }
    }

    return BestResult{{}, INF};
}