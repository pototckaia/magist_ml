#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <deque>
#include <queue>
#include <vector>

using namespace std;
using ll = int64_t;

struct Stop {
	ll from, start_time, to, finish_time;
};

int main() {
#ifdef _DEBUG
	std::string infile = "input.txt";
	std::string outfile = "output.txt";
	ios_base::sync_with_stdio(false);
	ifstream in(infile);
	ofstream out(outfile);
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
#endif

	ll n; cin >> n;
	ll start, end; cin >> start >> end; --start; --end;

	ll m; cin >> m;
	vector<Stop> bus(m);
	for (int i = 0; i < bus.size(); ++i) {
		cin >> bus[i].from >> bus[i].start_time >> bus[i].to >> bus[i].finish_time;
		bus[i].from--; bus[i].to--;
	}

	std::sort(bus.begin(), bus.end(), [](Stop& left, Stop& right) {
		return left.start_time < right.start_time;
	});

	vector<ll> distance(bus.size(), std::numeric_limits<ll>::max());
	distance[start] = 0;
	for (int i = 0; i < bus.size(); ++i) {
		if (bus[i].start_time >= distance[bus[i].from]) {
			distance[bus[i].to] = min(distance[bus[i].to], bus[i].finish_time);
		}
	}
	cout << (distance[end] == std::numeric_limits<ll>::max() ? -1ll : distance[end]);
}