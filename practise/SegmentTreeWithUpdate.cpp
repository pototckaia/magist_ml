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
    ll seqSize;
    ll halfSize;
    const ll null = 0;
	
public:
    void create(vll& a) {
        seqSize = a.size();

        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;

        halfSize = degreeSize;
        tree.resize(2 * degreeSize, null);

        for (ll i = 0; i < seqSize; ++i) {
            tree[degreeSize - 1 + i] = a[i];
        }

        for (ll i = degreeSize - 2; i >= 0; --i) {
            tree[i] = tree[2 * i + 1] + tree[2 * i + 2]; 
        }
    }

    ll get(ll left, ll right) {
        ll ans = null;
    	
        left += halfSize - 1; right += halfSize - 1;

        while (left < right) {
            if (left % 2 == 0) {
            	ans += tree[left];
            }
            if (right % 2 == 1)  {
            	ans += tree[right];
            }
            left = left / 2;
            right = right / 2 - 1;
        }
        if (left == right) {
        	ans += tree[left];
        }
        return ans;
    }

    void update (ll pos, ll val) {
    	auto v = halfSize - 1 + pos;
        tree[v]= val;
        while (v > 0) {
            v = (v - 1) >> 1;
            tree[v]= tree[2 * v + 1] + tree[2*v + 2];
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

	ll n, k; cin >> n >> k;
	vector<ll> a(n, 0);
	SegmentTree tree;
	tree.create(a);
	
	rep(i, 0, k) {
        char type; cin >> type;
		if (type == 'A') {
            ll index, value; cin >> index >> value;
			--index;
			tree.update(index, value);
		}
        else if (type == 'Q') {
            ll l, r; cin >> l >> r;
            --l; --r;
        	cout << tree.get(l, r) << endl;
        }
	}


	return 0;
}