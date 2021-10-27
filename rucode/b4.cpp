#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

using uns = uint64_t;
using ll = int64_t;

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
	vector<vector<pair<ll, ll>>> graph(n);
	vector<int> baron;
	for (ll i = 0; i < n; ++i) {
		int w; cin >> w;
		baron.push_back(w - 1);
	}
	for (ll i = 0; i < m; ++i) {
		ll a, b; cin >> a >> b; --a; --b;
		ll w = ll(baron[a] != baron[b]);
		graph[a].emplace_back(b, w);
		graph[b].emplace_back(a, w);
	}

	ll start = 0, end = n - 1;
	const auto emptyValue = std::numeric_limits<ll>::max();
	vector<ll> distance(graph.size(), emptyValue), parent(graph.size(), -1);
	deque<ll> d;

	d.push_back(start);
	distance[start] = 0;
	while (!d.empty()) {
		auto v = d.front();
		d.pop_front();

		for (auto i = 0u; i < graph[v].size(); ++i) {
			auto to = graph[v][i].first;
			auto w = graph[v][i].second;
			if (distance[to] > distance[v] + w) {
				distance[to] = distance[v] + w;
				parent[to] = v;
				if (w == 0) {
					d.push_front(to);
				}
				else {
					d.push_back(to);
				}
			}
		}
	}
	vector<uns> path;
	for (uns v = end; distance[end] != emptyValue && v != -1; v = parent[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());

	if (path.empty()) {
		cout << "impossible";
	}
	else {
		cout << distance[end] << " " << path.size() << endl;
		for (auto v: path) { cout << v + 1<< " "; }
	}
	//impossible
	//минимальную стоимость и количество посещенных городов, а во вторую выведите эти города в порядке посещени
	
	return 0;
}