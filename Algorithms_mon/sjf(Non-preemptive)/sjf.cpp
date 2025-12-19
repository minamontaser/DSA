//!sjf scheduling algorithm O(n^2), O(n)
#include <iostream>
#include <string>
#include <climits>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

struct task {
	string name;
	ll arrival, burst, start, wait, finish, tat;
	bool done = false;
};

signed main() {

	set_fast_io();

	ll n; cin >> n;
	vector<task> tasks(n);
	for (task& it : tasks) cin >> it.name >> it.arrival >> it.burst;
	ld total_wait = 0, total_tat = 0;
	ll completed = 0, time = 0;
	while (completed < n) {
		ll indx = -1, min_burst = LLONG_MAX;
		for (size_t i = 0; i < n; i++) {
			if (tasks[i].arrival <= time && !tasks[i].done && tasks[i].burst < min_burst) {
				min_burst = tasks[i].burst;
				indx = i;
			}
		}
		if (indx == -1) {
			ll next_arrival = LLONG_MAX;
			for (auto& it : tasks)
				if (!it.done)
					next_arrival = min(next_arrival, it.arrival);
			time = next_arrival;
			continue;
		}
		task& it = tasks[indx];
		it.done = true;
		it.start = time;
		time += it.burst;
		it.finish = time;
		it.tat = it.finish - it.arrival;
		it.wait = it.tat - it.burst;
		total_wait += it.wait, total_tat += it.tat;
		completed++;
	}

	cout << "\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n";
	for (auto& t : tasks) {
		cout << t.name << "\t" << t.arrival << "\t" << t.burst << "\t" << t.start
			<< "\t" << t.finish << "\t" << t.tat << "\t" << t.wait << "\n";
	}

	cout << "\nAverage Waiting Time = " << total_wait / n << endl;
	cout << "Average Turnaround Time = " << total_tat / n << endl;

	return 0;
}