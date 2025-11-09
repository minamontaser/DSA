//!SRTF (Shortest Remainig Time First)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

struct Task {
	string name;
	ll arrival, burst, complete, wait, remain, tat;
};

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n;
	cout << "Enter number of processes: ";
	cin >> n;

	vector<Task> tasks(n);
	cout << "Enter <Name> <Arrival Time> <Burst Time> for each process:\n";
	for (ll i = 0; i < n; i++) {
		cin >> tasks[i].name >> tasks[i].arrival >> tasks[i].burst;
		tasks[i].remain = tasks[i].burst;
	}

	ll completed = 0, time = 0;
	ld total_wait = 0, total_tat = 0;

	while (completed < n) {
		ll indx = -1, min_remain = INT_MAX;

		for (ll i = 0; i < n; i++) {
			if (tasks[i].arrival <= time && tasks[i].remain && tasks[i].remain < min_remain) {
				min_remain = tasks[i].remain;
				indx = i;
			}
		}

		time++;
		if (indx == -1) continue;
		tasks[indx].remain--;

		if (tasks[indx].remain == 0) {
			completed++;
			tasks[indx].complete = time;
			tasks[indx].tat = tasks[indx].complete - tasks[indx].arrival;
			tasks[indx].wait = tasks[indx].tat - tasks[indx].burst;

			total_wait += tasks[indx].wait, total_tat += tasks[indx].tat;
		}
	}

	cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
	for (int i = 0; i < n; i++) {
		cout << tasks[i].name << "\t"
			<< tasks[i].arrival << "\t"
			<< tasks[i].burst << "\t"
			<< tasks[i].complete << "\t"
			<< tasks[i].tat << "\t"
			<< tasks[i].wait << "\n";
	}

	cout << "\nAverage Waiting Time = " << total_wait / n << endl;
	cout << "Average Turnaround Time = " << total_tat / n << endl;

	return 0;
}