//!Merge sort O(n log n), O(n)
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

void merge(vector<ll>& vec_left, vector<ll>& vec_right, vector<ll>& vec) { // n
	ll l = 0, r = 0, i = 0; // 1
	while (l < vec_left.size() && r < vec_right.size())
		vec[i++] = (vec_left[l] >= vec_right[r] ? vec_right[r++] : vec_left[l++]); // n / 2
	while (l < vec_left.size()) vec[i++] = vec_left[l++]; // n / 2
	while (r < vec_right.size()) vec[i++] = vec_right[r++]; // n / 2
}

void mergeSort(vector<ll>& vec) { // n log n
	ll size = vec.size(), mid = size / 2;
	if (size <= 1) return; // base case
	vector<ll> vec_left(vec.begin(), vec.begin() + mid), vec_right(vec.begin() + mid, vec.end()); // n orrrrr O(1) with indices
	mergeSort(vec_left), mergeSort(vec_right); // log n
	merge(vec_left, vec_right, vec); // n
}