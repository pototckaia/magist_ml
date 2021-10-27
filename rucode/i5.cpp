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

    void create(ll size) {
        seqSize = size;

        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;

        halfSize = degreeSize;
        tree.resize(2 * degreeSize, null);
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
        return value_;
    }

    void update (ll pos, ll val) {
    	auto v = halfSize - 1 + pos;
        tree[v] = val;
        while (v > 0) {
            v = parent(v);
            tree[v] = tree[left(v)] + tree[right(v)]; 
        }
    }
};

ui cur = 0;
ui nextRand24(ui a, ui b) {
	cur = cur * a + b;
	return cur >> 8;
}

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

	ll n, m; cin >> n >> m;
	ll a, b; cin >> a >> b;
	vll ar(n);
	ll max_value = -1;
	rep(i, 0, n) {
		ar[i] = nextRand24(a, b) % m;
		max_value = max(ar[i], max_value);
	}

    // Инверсией называется пара индексов i и j такая, что i < j и a[i] > a[j]
    // Найти количество инверсий в данной перестановке.
	
	SegmentTree tree;
	tree.create(max_value + 1);

	ll inversion = 0;
	rep(i, 0, n) {
		inversion += ar[i] !=  max_value ? tree.get(ar[i] + 1, max_value) : 0;
		auto old = tree.get(ar[i], ar[i]);
		tree.update(ar[i],  old + 1);
	}
	cout << inversion;
	return 0;
}