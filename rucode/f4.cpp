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

ll Dijkstra(vector<vector<pair<ll, ll>>>& graph, ll start, ll end) {
	vector<bool> used(graph.size(), false);
	const auto defaultValue = std::numeric_limits<ll>::max();
	vector<ll> distance(graph.size(), defaultValue), parent(graph.size(), -1);

	distance[start] = 0;
	for (int i = 0; i < graph.size(); ++i) {
		int v = -1;
		for (int j = 0; j < graph.size(); ++j) {
			if (!used[j] && (v == -1 || distance[j] < distance[v])) {
				v = j;
			}
		}
		if (distance[v] == defaultValue) {
			break;
		}
		used[v] = true;
		for (int j = 0; j < graph[v].size(); ++j) {
			auto to = graph[v][j].first;
			auto w = graph[v][j].second;
			if (distance[v] + w < distance[to]) {
				distance[to] = distance[v] + w;
				parent[to] = v;
			}
		}
	}
	return distance[end] == defaultValue ? -1 : distance[end];
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

	ll n, s, f; cin >> n >> s >> f;
	--s; --f;
	vector<vector<pair<ll, ll>>> graph(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int w; cin >> w;
			if (w >= 0) {
				graph[i].emplace_back(j, w);
			}
		}
	}
	cout << Dijkstra(graph, s, f);
}