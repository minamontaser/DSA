// Dijkstra's Algorithm time: O((V + E) log V), space: O(V + E)
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <limits>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <optional>

using namespace std;

using ll = long long;
using ld = long double;
using size_t = std::size_t;

using Edge =  pair<size_t, ld>; // {neighbor, weight}
using State = pair<ld, size_t>; // {dist, node}

constexpr ld INF = numeric_limits<ld>::max();

struct DijkstraResult {
    vector<size_t> path;
    vector<ld> distances;
};

vector<size_t> reconstruct_path(size_t dest, const vector<size_t>& parent, const vector<ld>& dist){
    vector<size_t> path;

	if(dist[dest] == INF)
        return {};

    for(size_t v = dest; v != static_cast<size_t>(-1); v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    return path;
}

DijkstraResult Dijkstra(const vector<vector<Edge>>& adj_list, size_t src, optional<size_t> dest = nullopt){
	size_t n = adj_list.size();
	if(n == 0) throw invalid_argument("Empty adjacency list");

	vector<ld> dist(n, INF);
	vector<size_t> parent(n, static_cast<size_t>(-1));

	priority_queue<State, vector<State>, greater<State>> pq;
	//priority_queue<T, Container, Compair> //! Stores distance and the node

	if(src < 0 || src >= static_cast<size_t>(n))
    	throw out_of_range("Invalid source vertex");

	if(dest && (*dest < 0 || *dest >= static_cast<size_t>(n)))
		throw out_of_range("Invalid destination vertex");
	
	dist[src] = 0;
	pq.push({0, src});

	while(!pq.empty()){
		auto [curr_dist, u] = pq.top();
		pq.pop();

		if(curr_dist > dist[u]) continue;
		if(dest && u == *dest) break;

		for(const auto& [v, weight] : adj_list[u]){
			assert(weight >= 0);

			if(weight < 0)
				throw std::invalid_argument("Edge weights must be non-negative");

			if(v < 0 || v >= static_cast<size_t>(n))
    			throw out_of_range("Invalid vertex in adjacency list");

			if(curr_dist <= INF - weight && curr_dist + weight < dist[v]){
				dist[v] = curr_dist + weight;
				parent[v] = u;
				pq.push({dist[v], v});
			}
		}
	}

	if(dest)
		return DijkstraResult{reconstruct_path(*dest, parent, dist), dist};

	return DijkstraResult{{}, dist};
}