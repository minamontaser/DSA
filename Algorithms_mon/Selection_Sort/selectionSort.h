//!Selection sort O(n^2), O(1)
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

void selectionSort(vector<ll>& vec) {
	size_t n = vec.size();
	for (size_t i = 0; i < n - 1; i++) {
		size_t min_index = i;
		for (size_t j = i + 1; j < n; j++) {
			if (vec[j] < vec[min_index])
				min_index = j;
		}
		if (min_index != i)
			swap(vec[i], vec[min_index]);
	}
}