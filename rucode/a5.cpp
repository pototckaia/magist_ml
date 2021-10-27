#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

using ll = int64_t;
using ull = uint64_t;

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

	
    ull n, x, y, a; cin >> n >> x >> y >> a;
    ll t;
	ull m, z, b; cin >> m >> z >> t >> b;
	m <<= 1;
	
	vector<ll> prefix_sum;
    prefix_sum.push_back(0);
    prefix_sum.push_back(a);
	for (ull i = 2; i <= n; ++i) {
		// a_i = (x * a_i_1 + y) mod 2^16
		a = ((x * a + y) << 48) >> 48;
		prefix_sum.push_back(prefix_sum.back() + a);
	}

	ull sum_sum = 0;
	ull ci = 0, ci_1 = b % n;
	for (ull i = 1; i < m; ++i) {
		// b_i = (z * b_i_1 + t) mod 2^30
		// b_i = b_i mod n
		// min(c_2i, c_2i+1) max(c_2i, c_2i+1)

		b = ((z * b + t) << 34) >> 34;
		ci = ci_1; ci_1 = b % n;
		if (i % 2 == 0) continue;
		sum_sum += prefix_sum[max(ci, ci_1) + 1] - prefix_sum[min(ci, ci_1)];
	}
	cout << sum_sum;
    return 0;
}

//    ull n, m, x, y, z, a, b;
//    ll t;
//    cin >> n >> x >> y >> a >> m >> z >> t >> b;
//    m = m << 1;
//    for (int i = 0; i < n; ++i) {
//        s[i + 1] = s[i] + a;
//        a = ((x * a + y) << 48) >> 48;
//    }

//    ull total = 0;
//    ull c0 = 0, c = b % n;
//    for (int i = 1; i < m; ++i) {
//        ull k = ((z * b + t) << 34) >> 34;
//        c0 = c;
//        c = k % n;
//        b = k;
//        if (i % 2 == 0) continue;
//        total += s[max(c0, c) + 1] - s[min(c0, c)];
//    }
//    cout << total << endl;
//    return 0;
//}