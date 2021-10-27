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
//#ifdef _DEBUG
//	ios_base::sync_with_stdio(false);
//	ifstream in(infile);
//	ofstream out(outfile);
//	cin.rdbuf(in.rdbuf());
//	cout.rdbuf(out.rdbuf());
//#endif

	std::string a, b;
	cin >> a >> b;

	ll stra = a.size(), strb = b.size();
	vector<vector<ll>> dp(a.size() + 1, vector<ll>(b.size() + 1, 0));

	rep(i, 0, stra) {
		rep(j, 0, strb) {
			if (a[i] == b[j])
				dp[i + 1][j + 1] = max(dp[i][j] + 1, dp[i + 1][j + 1]);
			dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i + 1][j + 1]);
			dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j + 1]);			
		}
	}

	ll len = dp[stra][strb];
	ll i = stra - 1, j = strb - 1;
	vector<ll> resa(len), resb(len);

	while (len != 0 && i >= 0 && j >= 0) {
		if (a[i] == b[j]) {
			len--;
			resa[len] = i;
			resb[len] = j;
			j--; i--;
		}
		else {
			if (dp[i + 1][j + 1] == dp[i][j + 1])
				i--;
			else if (dp[i + 1][j + 1] == dp[i + 1][j])
				j--;
		}
	}

	cout << dp[stra][strb] << endl;
	for (auto i: resa) {
		cout << i + 1<< " ";
	}
	cout << endl;
	for (auto i: resb) {
		cout << i + 1<< " ";
	}
}
