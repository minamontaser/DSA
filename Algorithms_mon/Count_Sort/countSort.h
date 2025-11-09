//! Counting sort O(n + k), O(k)
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

void countSort(vector<ll>& vec, ll max_val) {
	size_t n = vec.size();
	vector<ll> freq(max_val + 1, 0);
	for (size_t i = 0; i < n; i++)
		freq[vec[i]]++;
	size_t index = 0;
	for (size_t i = 0; i <= max_val; i++) {
		for (size_t j = 0; j < freq[i]; j++)
			vec[index++] = i;
	}
}