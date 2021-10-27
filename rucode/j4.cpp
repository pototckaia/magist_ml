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

struct Road {
	Road() = default;
	Road(ll t, ll ti, ll w) : to(t), time(ti), weight(w) {}
	ll to;
	ll time, weight;
};

ll Dijkstra(vector<vector<Road>>& graph, ll start, ll end, ll countCup) {

	vector<bool> used(graph.size(), false);
	constexpr ll defaultValue = std::numeric_limits<ll>::max();
	vector<ll> times(graph.size(), defaultValue);

	times[start] = 0;
	for (int i = 0; i < graph.size(); ++i) {
		int v = -1;
		for (int j = 0; j < graph.size(); ++j) {
			if (!used[j] && (v == -1 || times[j] < times[v])) {
				v = j;
			}
		}
		if (times[v] == defaultValue) {
			break;
		}
		used[v] = true;
		for (int j = 0; j < graph[v].size(); ++j) {
			auto to = graph[v][j].to;
			auto time = graph[v][j].time	;
			if (times[v] + time < times[to] && countCup <= graph[v][j].weight) {
				times[to] = times[v] + time;
			}
		}
	}
	return times[end];
}

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

	ll n, m; cin >> n >> m;
	if (n == 1) {
		cout << 10000000;
		return 0;
	}
	
	vector<vector<Road>> graph(n);
	for (int i = 0; i < m; ++i) {
		ll v, u, time, w; cin >> v >> u >> time >> w;
		--v; --u;
		w = (w - 3000000) / 100;
		
		graph[v].emplace_back(u, time, w);
		graph[u].emplace_back(v, time, w);
	}

	ll left = 0, right = 10000000;
	while (right - left > 1) {
		ll mid = (left + right) / 2;
		auto shortPathTime = Dijkstra(graph, 0, n - 1, mid);
		if (shortPathTime <= 1440) {
			left = mid;
		}else {
			right = mid;
		}
	}
	cout << left << endl;
}