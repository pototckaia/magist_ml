#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

using ll = std::int64_t;

vector<ll> manaker(const string& s, bool isOdd) {
	vector<ll> d(s.length(), 0);
	ll n = s.length();

	ll left = 0, right = -1;
	if (isOdd) {
		for (ll i = 0; i < n; ++i) {
			ll k = i > right ? 1 : min(d[left + right - i], right - i + 1);
			while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) {  ++k; }
			d[i] = k;
			if (i + k - 1 > right) {
				left = i -k + 1;
				right = i + k - 1;
			}
		}
	}
	else {
		for (ll i = 0; i < n; ++i) {
			ll k = i > right ? 0 : min(d[left + right - i + 1], right - i + 1);
			while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) { ++k; }
			d[i] = k;
			if (i + k - 1 > right) {
				left = i - k;  right = i + k - 1;
			}
		}
	}
	return d;
}

ll countPalindrome(const string& s) {
	auto d1 = manaker(s, true);
	auto d2 = manaker(s, false);
	ll ans = 0;
	for (auto i = 0; i < d1.size(); ++i) {
		ans += d1[i] + d2[i] - 1;
	}
	return ans;
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

	string s; cin >> s;
	cout << countPalindrome(s);
	return 0;
}
