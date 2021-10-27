#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using ll = std::int64_t;
using ull = std::uint64_t;
using ui = std::uint32_t;
using vll = std::vector<ll>;
using namespace std;

#define rep(i, a, b) for (ll (i) = (a); (i) < (b); ++(i))


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

	std::string s; cin >> s;
	vector<ll> p_open(s.size()), p_close(s.size());
	ll op = 0, cl = 0;
	rep(i, 0, s.size()) {
		p_open[i] = (i == 0 ? 0 : p_open[i - 1]);
		p_close[i] = (i == 0 ? 0 : p_close[i - 1]);
		if (s[i] == '(') {
			++p_open[i];
		} else {
			++p_close[i];
		}
	}
	
	ll q; cin >> q;
	rep(i, 0, q)
	{
		ll l, r; cin >> l >> r;
		--l; --r;
		
		auto cl = p_close[r] - (l == 0 ? 0 : p_close[l - 1]);
		auto op = p_open[r] - (l == 0 ? 0 : p_open[l - 1]);
		if (cl == op)
		{
			cout << 1;
		}
		else
		{
			cout << 0;
		}
		
	}
	return 0;
}