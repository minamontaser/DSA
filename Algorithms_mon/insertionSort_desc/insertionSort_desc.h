//!Insertion sort O(n^2), O(1)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long

void insertionSort(vector<ll>& vec) {
	ll temp;
	for (ll i = 1; i < vec.size(); i++) {
		ll j = i - 1;
		temp = vec[i];
		while (j >= 0 && vec[j] < temp) {
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = temp;
	}
}