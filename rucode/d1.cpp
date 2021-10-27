#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#define rep(i, start, end) for (auto i(start); (i) < (end); ++(i))
#define rep_d(i, start, end) for (auto i(start); (i) >= (end); --(i))

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

	std::string s1, s2;
	cin >> s1 >> s2;

	ll m = s1.size(), n = s2.size();
	vector<vector<ll>> dp(m + 1, vector<ll>(n + 1, 0ll));
	rep(j, 1, n + 1) {
		dp[0][j] = j;
	}
	rep(i, 1, m + 1) {
		dp[i][0] = i;
	}
	rep(i, 1, m + 1) {
		rep(j, 1, n + 1) {
			if (s1[i - 1] != s2[j - 1]) {
				dp[i][j] = min(dp[i - 1][j] + 1ll,
					min(dp[i][j - 1] + 1ll,
					dp[i - 1][j - 1] + 1ll));
			}
			else
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
		}
	}
	cout << dp[m][n];
}
