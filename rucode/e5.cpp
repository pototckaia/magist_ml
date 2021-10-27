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

class SegmentTree {
    vll tree;
	vll indexs;
    ll seqSize;
    ll halfSize;

public:
    void create(vll& a) {
        seqSize = a.size();

        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;

        halfSize = degreeSize;
        tree.resize(2 * degreeSize, numeric_limits<ll>::min());
        indexs.resize(2 * degreeSize, 0);

        for (ll i = 0; i < seqSize; ++i) {
            tree[degreeSize - 1 + i] = a[i];
            indexs[degreeSize - 1 + i] = i;
        }

        for (ll i = degreeSize - 2; i >= 0; --i) {
            if (tree[2 * i + 1] > tree[2 * i + 2]) {
                tree[i] = tree[2 * i + 1];
                indexs[i] = indexs[2 * i + 1];
            } else {
                tree[i] = tree[2 * i + 2];
                indexs[i] = indexs[2 * i + 2];
            }
        }
    }

    ll getIndex(ll left, ll right) {
        ll ans = numeric_limits<ll>::min();
        ll index = 0;
    	
        left += halfSize - 1; right += halfSize - 1;

        while (left < right) {
            if (left % 2 == 0 && ans < tree[left]) {
            	ans = tree[left];
            	index = indexs[left];
            }
            if (right % 2 == 1 && ans < tree[right])  {
            	ans = tree[right];
            	index = indexs[right];
            }
        	
            left = left / 2;
            right = right / 2 - 1;
        }
        if (left == right && ans < tree[left]) {
        	ans = tree[left];
        	index = indexs[left];
        }
    	
        return index;
    }

};

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

	ll n; cin >> n;
	vector<ll> a(n);
	rep(i, 0, n) { cin >> a[i]; }
    SegmentTree tree;
	tree.create(a);

	ll k; cin >> k;
	rep(i, 0, k) {
		ll l, r; cin >> l >> r;
		--l; --r;
		
		auto ii = tree.getIndex(l, r);
		cout << a[ii] << " " << ii + 1 << endl;
	}


	return 0;
}