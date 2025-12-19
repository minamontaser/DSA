//Floyd Warshall Algorithm O(V^3) -> O(N^2 * N), O(V^2)
#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

const ll INF = LLONG_MAX / 4;

void floyd_warshall(vector<vector<ll>>& floyd_mat, ll n) {
	for (size_t k = 0; k < n; k++) {
		for (size_t i = 0; i < n; i++) {
			if (floyd_mat[i][k] == INF) continue;
			for (size_t j = 0; j < n; j++) {
				if (floyd_mat[k][j] == INF) continue;
				floyd_mat[i][j] = min(floyd_mat[i][j], floyd_mat[i][k] + floyd_mat[k][j]);
			}
		}
	}
}

signed main() {

	set_fast_io();

	ll n; cin >> n;
	vector<vector<ll>> floyd_mat(n, vector<ll>(n));
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			cin >> floyd_mat[i][j];
	floyd_warshall(floyd_mat, n);
	cout << "\nfloydMat: " << endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cout << floyd_mat[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	return 0;
}