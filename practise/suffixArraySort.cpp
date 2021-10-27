#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#define rep(i, start, end) for (auto i(start); i < end; ++i)

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

	string text; cin >> text;
	text += "$";
	ll n = text.size();
	vector<ll> suffixArray(n), equivalent(n);

	rep(i, 0, n) { 
		suffixArray[i] = i; 
		equivalent[i] = text[i]; 
	}

	vector<pair<ll, ll>> equivalen_part(n);
	for (ll degree(1); degree < n; degree <<= 1) {
		rep(i, 0, n) { 
			equivalen_part[i] = { equivalent[i], equivalent[(i + degree) % n] };
		}
		sort(suffixArray.begin(), suffixArray.end(), [&](auto x, auto y) {
			return equivalen_part[x] < equivalen_part[y];
			});
		rep(i, 1, n) {
			auto increase(equivalen_part[suffixArray[i - 1]] != equivalen_part[suffixArray[i]]);
			equivalent[suffixArray[i]] = equivalent[suffixArray[i - 1]] + increase;
		}
	}

	for (auto s : suffixArray) {
		cout << s << " ";
	}
}