#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

using ll = std::int64_t;
using ull = std::uint64_t;

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

    const ull n = s.length();
    const ull p = 31;
    vector<ull> pow_h(n);
	vector<ull> h(n);
	
    pow_h[0] = 1u;
    for (ull i = 1; i < n; ++i) {
        pow_h[i] = pow_h[i - 1] * p; 
    }

    for (ull i = 0; i < n; ++i) {
        h[i] = ull(s[i] - 'a' + 1) * pow_h[i];
        if (i == 0) {
            continue;
        }
        h[i] += h[i - 1];
    }

    ull m; cin >> m;
    for (int i = 0; i < m; ++i) {
        ull a, b, c, d; cin >> a >> b >> c >> d;

    	if (b - a != d - c) {
            cout << "No" << endl;
            continue;
        }
    	
        if (a == c and b == d) {
            cout << "Yes" << endl;
            continue;
        }
    	
        ull h1 = h[b - 1] - (a > 1 ? 1 : 0) * h[a - 2];
        ull h2 = h[d - 1] - (c > 1 ? 1 : 0) * h[c - 2];

    	if (a < c && h1 * pow_h[c - a] == h2 || a > c && h2 * pow_h[a - c] == h1) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
	
	return 0;
}
