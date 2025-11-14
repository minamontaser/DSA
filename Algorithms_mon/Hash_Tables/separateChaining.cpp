#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int indexC(ll e, ll h) {
	return (e % h);
}

vector<vector<ll>> separateC(vector<ll>& vec, ll n, ll h) {
	vector<vector<ll>> hashT(h);
	for (size_t i = 0; i < n; i++) {
		int indx = indexC(vec[i], h);
		hashT[indx].push_back(vec[i]);
	}
	return hashT;
}

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n, h; cin >> n >> h;
	vector<ll> vec(n);
	for (ll& x : vec) cin >> x;
	vector<vector<ll>> hashT = separateC(vec, n, h);
	for (const auto& bucket : hashT) {
		if (bucket.empty()) {
			cout << -1 << endl;
			continue;
		}
		for (ll x : bucket) {
			cout << x << " ";
		}
		cout << "\n";
	}

	return 0;
}