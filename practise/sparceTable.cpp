#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using ll = std::int64_t;
using ull = std::uint64_t;
using namespace std;

#define rep(i, a, b) for (ll (i) = (a); (i) < (b); ++(i))

class sparseTable {
public:
	sparseTable(vector<ll>& a) : logs(a.size() + 1) {
        auto n = static_cast<ull>(a.size());

		logs[1] = 0;
        for (ull i = 2; i <= n; ++i) {
            logs[i] = logs[static_cast<size_t>(i / 2)] + 1;
        }
		s.resize(logs[n] + 1, vector<ll>(n));

		for (ull i = 0; i < n; ++i) {
			s[0][i] = a[i];
		}
		for (ull level = 1; (1 << level) <= n; ++level) {
			for (ull i = 0; i + (1 << level) <= n; ++i) {
				s[level][i] = func(
					s[level - 1][i],
					s[level - 1][i + (1 << (level - 1))]);
			}
		}
	}

	ll get(ll l, ll r) {
		ll len = r - l + 1;
		ll level = logs[len];
		return func(
			s[level][l],
			s[level][r - (1 << level) + 1]); 
	}

private:
	vector<vector<ll>> s;
	vector<ll> logs;

	ll func(ll value1, ll value2) {
		return max(value1, value2);
	}
};

int main() {
    
}