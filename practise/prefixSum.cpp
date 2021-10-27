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


template <typename T>
class PrefixSum {
private:
	vector<T> pref;

public:
	PrefixSum(vector<T>& a) {
		if (a.empty()) { return; }

		pref.push_back(a.front());
		for (ll i = 1; i < a.size(); ++i) {
			pref.push_back(pref.back() + a[i]);
		}
	}

	T get(ll l, ll r) {
		if (l >= pref.size() && r >= pref.size())  { return T(0); }

		auto right = min((ll)pref.size() - 1, r);
		auto left = min((ll)pref.size() - 1, l);

		return pref[right] - (left <= 0 ? 0 : pref[left - 1]);
	}
};

int main() {

}