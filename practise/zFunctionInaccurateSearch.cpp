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

bool isPalindrom(const std::string& s, int left, int right) {
	while (left <= right) {
		if (left >= s.size() || right < 0 || 
			s[left++] != s[right--]) {
			return false;
		}
	}
	return true;
}

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

	string rev_text(text.rbegin(), text.rend());
	string rev_pattern(pattern.rbegin(), pattern.rend());

	auto z1(getZ(pattern + "^" + text));
	auto z2(getZ(rev_pattern + "^" + rev_text));

	vector<uns> index;
	for (ll i = 0; text.size() >= pattern.size() && i <= text.size() - pattern.size(); ++i) {
		auto a(z1[pattern.size() + 1 + i]);
		auto b(z2[text.size() - i + 1]);
		if (a + b >= static_cast<ll>(pattern.size()) - k) {
			index.push_back(i);
		}
	}

	cout << index.size() << endl;
	for (auto i : index) { cout << i + 1 << " "; }
}

