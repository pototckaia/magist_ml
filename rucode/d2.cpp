#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#define FOR(i, start, end) for (long long i = (start); i < static_cast<long long>(end); ++i)

std::string infile = "input.txt";
std::string outfile = "output.txt";

using uns = unsigned;
using ull = unsigned long long;
using ll = long long;

using namespace std;

std::vector<ll> getZ(const std::string& s) {
	std::vector<ll> z(s.size(), 0);
	ll l(0), r(0);
	FOR(i, 1, s.size()) {
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
	std::string text, pattern; cin >> text >> pattern;
	ll k; cin >> k;

	auto z1(getZ(pattern + "^" + text));

	vector<uns> index;
	for (int i = 0; i < z1.size(); ++i) {
		if (z1[i] == static_cast<ll>(pattern.size())) {
			index.push_back(i - pattern.size() - 1);
		}
	}

	cout << index.size() << endl;
	for (auto i : index) { cout << i + 1 << " "; }
}

