#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

void BFS(vector<vector<ll>>& adj, vector<bool>& visited, queue<ll>& que) {
	if (que.empty()) return;
	ll node = que.front(), size = adj.size();
	que.pop();
	cout << node << " ";
	for (ll i = 0; i < size; i++) {
		if (adj[node][i] == 1 && !visited[i]) {
			visited[i] = true;
			que.push(i);
		}
	}
	BFS(adj, visited, que);
}

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n = 6;;
	vector<vector<ll>> adj = {
		{0,1,1,0,0,0},
		{1,0,0,1,1,0},
		{1,0,0,0,1,0},
		{0,1,0,0,0,1},
		{0,1,1,0,0,1},
		{0,0,0,1,1,0}
	};

	vector<bool> visited(6, false);
	queue<ll> que;

	ll start = 0;
	visited[start] = true;
	que.push(start);

	cout << "BFS traversal (recursive, adjacency matrix): ";
	BFS(adj, visited, que);
	cout << "\n";

	return 0;
}