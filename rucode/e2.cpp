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

std::vector<unsigned> getZ(const std::vector<ll>& s) {
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
	ll n, m; cin >> n >> m;
	vector<ll> a(n);
	for(ll i(0); i < n; ++i) { cin >> a[i]; }
	vector<ll> reversed(a.rbegin(), a.rend());

	auto a_z = a;
	a_z.push_back(m + 1);
	a_z.insert(a_z.end(), reversed.begin(), reversed.end());
	auto z(getZ(a_z));

	vector<ll> count;
	for (ll i(a.size() - 1); i >= 0; --i) {
		ll j = 2 * a.size() - 2 * i + 1;
		if (j >= z.size() || z[j] >= i) {
			count.push_back(a.size() - i);
		}
	}

	for (auto c: count) 
		cout << c << " ";
}
// 0 1 2 3 4 5 6 7 8 9  10 11 12
// 0 1 0 0 2 1 0 6 1 0  0  2  1
// 1 1 2 2 1 1 & 1 1 2  2  1  1
//               

//6 2 1