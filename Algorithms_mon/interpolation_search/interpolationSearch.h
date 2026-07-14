// interpolationSearch.h time: O(1) best, O(log log n) average, O(n) worst --- space: O(1) in all cases
#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

ll interpolationSearch(const vector<ll>& vec, ll target) {
    if (vec.empty()) return -1;

    size_t low = 0, high = vec.size() - 1;

    while (low <= high && target >= vec[low] && target <= vec[high]) {

        if (vec[low] == vec[high])
            return (vec[low] == target) ? low : -1;

        size_t pos = low +
            static_cast<size_t>(
                (static_cast<ld>(target - vec[low]) *
                 (high - low)) /
                (vec[high] - vec[low]));

        if (vec[pos] < target) {
            low = pos + 1;
        }
		else if (vec[pos] > target) {
            if (pos == 0) break;
            high = pos - 1;
        }else {
            return pos;
        }
    }

    return -1;
}