//! FCFS (First Come First Serve) Scheduling Algorithm, O(n log n), O(n)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

struct task {
	string name;
	ll arrival, burst, start, wait, tat, finish;
};

void merge(vector<task>& tasks, vector<task>& left_pr, vector<task>& right_pr) {
	ll l = 0, r = 0, i = 0;
	while (l < left_pr.size() && r < right_pr.size())
		tasks[i++] = (left_pr[l].arrival >= right_pr[r].arrival ? right_pr[r++] : left_pr[l++]);
	while (l < left_pr.size()) tasks[i++] = left_pr[l++];
	while (r < right_pr.size()) tasks[i++] = right_pr[r++];
}

void mergeSort(vector<task>& tasks) {
	ll size = tasks.size(), mid = size / 2;
	if (size <= 1) return;
	vector<task> left_pr(tasks.begin(), tasks.begin() + mid), right_pr(tasks.begin() + mid, tasks.end());
	mergeSort(left_pr), mergeSort(right_pr);
	merge(tasks, left_pr, right_pr);
}

ld get_average_wt(const ld& wt) {
	return wt;
}

ld get_average_tat(const ld& tat) {
	return tat;
}

void fcfs_scheduling(vector<task>& tasks, ll n) {
	mergeSort(tasks);
	ld average_wt = 0, average_tat = 0;
	for (ll i = 0; i < n; i++) {
		tasks[i].start = max((i == 0 ? 0 : tasks[i - 1].finish), tasks[i].arrival);
		tasks[i].finish = tasks[i].start + tasks[i].burst;
		tasks[i].wait = abs(tasks[i].start - tasks[i].arrival);
		tasks[i].tat = tasks[i].wait + tasks[i].burst;
		average_wt += tasks[i].wait;
		average_tat += tasks[i].tat;
	}
	average_wt /= n, average_tat /= n;
	get_average_wt(average_wt);
	get_average_tat(average_tat);
}

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n;
	cout << "Enter no.process: "; cin >> n;
	vector<task> tasks(n);

	for (ll i = 0; i < n; i++) {
		cout << "Enter proccess name, arrival and burst time: ";
		cin >> tasks[i].name >> tasks[i].arrival >> tasks[i].burst;
	}

	fcfs_scheduling(tasks, n);

	cout << "PName\tArrive\tBurst\tStart\tFinish\tTAT\tWait\n";
	for (ll i = 0; i < n; i++) {
		cout << tasks[i].name << "\t" << tasks[i].arrival << "\t"
			<< tasks[i].burst << "\t" << tasks[i].start << "\t"
			<< tasks[i].finish << "\t" << tasks[i].tat << "\t" << tasks[i].wait << "\n";
	}

	cout << "Average Waiting Time: " << get_average_wt() << "\n";
	cout << "Average Turnaround Time: " << get_average_tat() << "\n";

	return 0;
}