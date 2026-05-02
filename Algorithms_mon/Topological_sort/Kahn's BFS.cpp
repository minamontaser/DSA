#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

vector<ll> topoSort(const vector<vector<ll>>& dag, ll v) {
	vector<ll> in_degree(v, 0);
	vector<ll> topo;
	queue<ll> que;
	for (size_t u = 0; u < v; u++)
		for (size_t t = 0; t < v; t++)
			if (dag[u][t] == 1) in_degree[t]++;
	for (ll& deg : in_degree)
		if (deg == 0) que.push(&deg - &in_degree[0]); // push index(i) of vertex with indegree 0
	while (!que.empty()) {
		ll temp_u = que.front();
		que.pop();
		topo.push_back(temp_u);
		for (size_t t = 0; t < v; t++)
			if (dag[temp_u][t] == 1)
				if (--in_degree[t] == 0) que.push(t);
	}
	if (topo.size() != v) {
		cout << "Graph has a cycle, Topological Sort not possible.\n";
		return {};
	}
	return topo;
}

signed main() {

	set_fast_io();

	ll v; cin >> v;
	vector<vector<ll>> dag(v, vector<ll>(v, 0));
	for (size_t u = 0; u < v; u++)
		for (ll& t : dag[u])
			cin >> t;
	vector<ll> topo = topoSort(dag, v);
	cout << "\nTopological Sort (Kahn's): ";
	for (size_t i = 0; i < v; i++)
		cout << topo[i] << (i == v - 1 ? "\n" : " -> ");

	return 0;
}