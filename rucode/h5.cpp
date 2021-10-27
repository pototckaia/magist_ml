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
    ll null = 0;
	
    ll seqSize = 0u;
    ll halfSize = 0u;
	
public:
    inline ll left(ll v) { return 2 * v + 1; }
    inline ll right(ll v) { return 2 * v + 2; }
    inline ll parent(ll v) { return (v - 1) >> 1; }

	inline ll isOdd(ll v) { return ll(v % 2 == 0) - ll(v % 2 != 0); }

    void create(vll& a) {
        seqSize = a.size();

        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;

        halfSize = degreeSize;
        tree.resize(2 * degreeSize, null);
        
        for (ll i = 0; i < seqSize; ++i) {
        	auto tmp  = isOdd(i);
            tree[degreeSize - 1 + i] = isOdd(i) * a[i];
        }

        for (ll i = degreeSize - 2; i >= 0; --i) {
            tree[i] = tree[left(i)] + tree[right(i)]; 
        }
    }

    ll get(ll l, ll r) {
        ll value_ = null;
    	
        auto left = l + halfSize - 1, right = r + halfSize - 1;

        while (left < right) {
            if (left % 2 == 0) {
            	value_ += tree[left];
            }
            if (right % 2 == 1)  {
            	value_ += tree[right];
            }
            left = left / 2;
            right = right / 2 - 1;
        }
        if (left == right) {
            value_ += tree[left];
        }
        return isOdd(l) * value_;
    }

    void update (ll pos, ll val) {
    	auto v = halfSize - 1 + pos;
        tree[v] = isOdd(pos) * val;
        while (v > 0) {
            v = parent(v);
            tree[v] = tree[left(v)] + tree[right(v)]; 
        }
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
	vll a(n);
	rep(i, 0, n) { cin >> a[i]; }

	SegmentTree tree;
	tree.create(a);
	
	ll m; cin >> m;
    rep(_, 0, m)
    {
	    ll type; cin >> type;
        ll i, j; cin >>  i >> j;
    	if (type == 0) {
    		--i;
    		tree.update(i, j);
    	} else {
	        --i; --j;
    		cout << tree.get(i, j) << endl;
        }
    }

	return 0;
}