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

void dfs (int v, vector<bool>& used, vector<vector<ll>>& graph) {
	used[v] = true;
	for (size_t i= 0; i< graph[v].size(); ++i) {
		int to = graph[v][i];
		if (!used[to]) {
			dfs(to, used, graph);
		}
	}
}

ll countWeakConnectivity(vector<vector<ll>>& g) {
	vector<vector<ll>> graph(g.size());
	for (int v = 0; v < g.size(); ++v) {
		for (int i = 0; i < g[v].size(); ++i) {
			auto t = g[v][i];
			graph[v].push_back(t);
			graph[t].push_back(v);
		}
	}
	
	vector<bool> used(graph.size(), false);
	ll count = 0;
	for (int i = 0; i < graph.size(); ++i) {
		if (!used[i]) {
			dfs(i, used, graph);
			++count;
		}
	}
	return count;
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

	ll n; cin >> n;
	vector<vector<ll>> graph(n);
	for (int i = 0; i < n; ++i) {
		int j; cin >> j; --j;
		if (i != j) {
			graph[i].push_back(j);
		}
	}

	int ans =countWeakConnectivity(graph);
	cout << ans;
}