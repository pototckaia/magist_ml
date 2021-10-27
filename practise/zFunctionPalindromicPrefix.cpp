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

bool isPalindrom(const std::string& s, int left, int right) {
	while (left <= right) {
		if (left >= s.size() || right < 0 || 
			s[left++] != s[right--]) {
			return false;
		}
	}
	return true;
}

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
	std::string s; cin >> s;
	string reversed(s.rbegin(), s.rend());
	auto z(getZ(s + "&" + reversed));

	unsigned count(1);
	for (unsigned i(s.size() + 1); i < z.size(); ++i) {
		count = max(count, z[i]);
	}
	cout << count;
}
