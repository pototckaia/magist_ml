#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

std::string infile = "input.txt";
std::string outfile = "output.txt";

using uns = unsigned;
using ull = unsigned long long;
using ll = long long;

using namespace std;

int main(int argc, char* argv[]) {

#ifdef _DEBUG
	ios_base::sync_with_stdio(false);
	ifstream in(infile);
	ofstream out(outfile);
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
#endif
	string s;
	cin >> s;

	vector<int> p(s.size(), 0);
	int c = 0;
	for (int i = 1; i < p.size(); ++i) {
		while (c > 0 && s[i] != s[c]) {
			c = p[c - 1];
		}
		if (s[i] == s[c]) {
			++c;
		}
		p[i] = c;
	}

	vector<ll> dp(s.size(), 0);
	ll dp_max(0);
	for (ll i = 0; i < dp.size(); ++i) {
		if (p[i] >= 1) {
			dp[i] = dp[p[i] - 1] + 1;
			dp_max = max(dp_max, dp[i]);
		}
	}

	ll ans(0);
	for (ll i = 0; i < dp.size(); ++i) {
		if (dp[i] == dp_max) {
			ans = i + 1;
			break;
		}
	}
	cout << s.substr(0, ans) << endl;
}
