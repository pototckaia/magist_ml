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
    vll min_tree;
    ll min_null = numeric_limits<ll>::max();

	vll max_tree;
    ll max_null = numeric_limits<ll>::min();
	
    ll seqSize = 0u;
    ll halfSize = 0u;
	
public:
    inline ll left(ll v) { return 2 * v + 1; }
    inline ll right(ll v) { return 2 * v + 2; }
    inline ll parent(ll v) { return (v - 1) >> 1;; }
	
    void create(vll& a) {
        seqSize = a.size();

        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;

        halfSize = degreeSize;
        min_tree.resize(2 * degreeSize, min_null);
        max_tree.resize(2 * degreeSize, max_null);

        for (ll i = 0; i < seqSize; ++i) {
            min_tree[degreeSize - 1 + i] = a[i];
            max_tree[degreeSize - 1 + i] = a[i];
        }

        for (ll i = degreeSize - 2; i >= 0; --i) {
            min_tree[i] = min(min_tree[left(i)], min_tree[right(i)]); 
            max_tree[i] = max(max_tree[left(i)], max_tree[right(i)]); 
        }
    }

    ll getDiff(ll left, ll right) {
        ll min_v = min_null;
        ll max_v = max_null;
    	
        left += halfSize - 1; right += halfSize - 1;

        while (left < right) {
            if (left % 2 == 0) {
            	min_v = min(min_v, min_tree[left]);
            	max_v = max(max_v, max_tree[left]);
            }
            if (right % 2 == 1)  {
            	min_v = min(min_v, min_tree[right]);
            	max_v = max(max_v, max_tree[right]);
            }
            left = left / 2;
            right = right / 2 - 1;
        }
        if (left == right) {
            min_v = min(min_v, min_tree[left]);
            max_v = max(max_v, max_tree[left]);
        }
        return max_v - min_v;
    }

    void update (ll pos, ll val) {
    	auto v = halfSize - 1 + pos;
        min_tree[v]= val;
        max_tree[v]= val;
        while (v > 0) {
            v = parent(v);
            min_tree[v] = min(min_tree[left(v)], min_tree[right(v)]); 
            max_tree[v] = max(max_tree[left(v)], max_tree[right(v)]); 
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

	ll k; cin >> k;
	ll n = 0;
	vector<pair<ll, ll>> q(k);
	rep(i, 0, k) {
		cin >> q[i].first >> q[i].second;
        if (q[i].first > 0) {
			n = max(n, q[i].second);
		} else {
            n = max(n, abs(q[i].first));
        }
	}

	vector<ll> a(n + 1, 0);
	rep(i, 0, n + 1) {
		a[i] = (i * i) % 12345 + (i * i * i) % 23456;
	}
	SegmentTree tree;
    tree.create(a);
	
	for (auto& qq: q)
	{
		if (qq.first > 0) {
			cout << tree.getDiff(qq.first, qq.second) << endl;
		}
        else {
	        tree.update(abs(qq.first), qq.second);
        }
	}

	return 0;
}