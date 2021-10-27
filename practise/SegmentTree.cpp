#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
 
using namespace std;
 
using ll = long long;
using vll = vector<ll>;
#define x           first
#define y           second
#define all(a)      (a).begin(),(a).end()
#define rep(i,a,b)  for(int i=a;i<b;++i)
 
class SegmentTree {
    vll tree;
    ll seqSize;
    ll halfSize;
 
    void create(vll& a) {
        seqSize = a.size();
 
        ll degreeSize = 1;
        while (degreeSize < seqSize) degreeSize <<= 1;
 
        halfSize = degreeSize;
        tree.resize(2 * degreeSize, numeric_limits<ll>::min());
 
        for (ll i = 0; i < seqSize; ++i) {
            tree[degreeSize - 1 + i] = a[i];
        }
 
        for (ll i = degreeSize - 2; i >= 0; --i) {
            tree[i] = std::max(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }
 
    ll get(ll left, ll right) {
        ll ans = numeric_limits<ll>::min();
 
        left += halfSize - 1; right += halfSize - 1;
 
        while (left < right) {
            if (left % 2 == 0) ans = max(ans, tree[left]); // odd
            if (right % 2 == 1) ans = max(ans, tree[right]); // not odd
 
            left = left / 2;
            right = right / 2 - 1;
        }
        if (left == right) ans = max(ans, tree[left]);
 
        return ans;
    }
};
 
int main()
{
    int n, w;
    cin >> n >> w;
    vector<ll> v, ans_(w, 0), z(w, 0);
    vll left, right;
 
    for (int i = 0; i < n; ++i) {
        int size_a;
        cin >> size_a;
        v.resize(size_a);
        rep(j, 0, size_a) {
            cin >> v[j];
        }
 
        SegmentTree::create(v);
        rep(j, 0, size_a) {
            ll left = max(0, j - w + size_a);
            ll ans = numeric_limits<ll>::min();
            if (w - size_a > j) { ans = 0; }
            ans_[j] += max(ans, SegmentTree::get(left, j));
 
        }
        if (size_a < w) {
            ll h = w - size_a;
            ll f = max(SegmentTree::get(max(size_a - h, 0ll), size_a - 1), 0ll);
            if (size_a + 1 <= h) {
                z[size_a] += f;
                z[h] -= f;
            }
            for (int j = 1; j <= size_a; j++) {
                if (w - size_a + j <= size_a) {
                    continue;
                }
                ans_[w - size_a + j - 1] += max(SegmentTree::get(j - 1, size_a - 1), 0ll);
            }
        }
    }
 
    rep(i, 0, w) {
        z[i] += i - 1 >= 0 ? z[i - 1] : 0;
        cout << ans_[i] + z[i] << " ";
    }
}