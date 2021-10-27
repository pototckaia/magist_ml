#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#define rep(i, start, end) for (auto i(start); (i) < (end); ++(i))
#define rep_d(i, start, end) for (auto i(start); (i) >= (end); --(i))

std::string infile = "input.txt";
std::string outfile = "output.txt";

using uns = unsigned;
using ull = unsigned long long;
using ll = long long;

using namespace std;

std::vector<unsigned> getZ(const std::string& s) {
	std::vector<unsigned> z(s.size(), 0);
	unsigned l(0u), r(0u);
	for (unsigned i(1u); i < s.size(); ++i) {
		if (i <= r) {
			z[i] = min(z[i - l], r - i + 1);
		}
		while (z[i] + i < s.size() && s[z[i]] == s[z[i] + i]) {
			++z[i];
		}
		if (r < i + z[i] - 1) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

int main(int argc, char* argv[]) {

#ifdef _DEBUG
	ios_base::sync_with_stdio(false);
	ifstream in(infile);
	ofstream out(outfile);
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
#endif
	ll n; cin >> n;
	vector<ll> p(n);
	rep(i, 0, n) { cin >> p[i]; }

	vector<ll> z(n); 
	rep(i, 1, n) {
		z[i - p[i] + 1] = max(0ll, p[i]);
	}
	z[0] = n;

	ll i(1);
	while (i < n) {
		ll t = i;
		if (z[i] > 0) {
			rep(j, 1, z[i]) {
				if (z[i + j] > z[j]) { break; }
				z[i + j] = min(z[j], z[i] - j);
				t = i + j;
			}
		}
		i = t + 1;
	}
	
	rep(i, 0, n) { cout << z[i] << " "; }
}

