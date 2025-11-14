#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int indexQ(ll e, ll h, ll it) {
	return ((e % h) + it * it) % h;
}

vector<ll> quadraticP(vector<ll>& vec, ll n, ll h) {
	vector<ll> hashT(h, -1);
	for (size_t i = 0; i < n; i++) {
		int it = 0, indx = indexQ(vec[i], h, it);
		while (hashT[indx] != -1 && it < h) {
			indx = indexQ(vec[i], h, ++it);
		}
		hashT[indx] = vec[i];
	}

	return hashT;
}

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n, h;  cin >> n >> h;
	vector<ll> vec(n), hashT;
	for (ll& x : vec) cin >> x;
	hashT = quadraticP(vec, n, h);
	for (ll x : hashT) cout << x << endl;

	return 0;
}