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

ll  binary_search(vector<ll>& d, ll a) {
	ll l = 0, r = d.size() - 1;
	while (r - l > 1) {
		ll mid = (l + r) / 2;
		if (d[mid] >= a) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return r;
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
	vector<ll> a(n);
	rep(i, 0, n) { cin >> a[i]; }

	ll len = 0;
	vector<ll> d(n + 1 , std::numeric_limits<ll>::max());
	d[0] = std::numeric_limits<ll>::min();

	rep(i, 0, n) {
		ll j = binary_search(d, a[i]);
		if (d[j - 1] < a[i] && a[i] < d[j]) {
			d[j] = a[i];
			len = max(len, j);
		}
	}

	cout << n - len;
}
