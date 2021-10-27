#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <exception>
#include <cassert>
#include <random>
 
using namespace std;
 
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
 
class SegmentAdditionTree {
 
private:
 
    // common
    struct Result {
        ll min, pos;
        Result(ll v, ll p) : min(v), pos(p) {}
    };
    using MetaInformation = ll; // inconsistency
 
    const Result identity = Result(INT_MAX, -1);
    const MetaInformation metaIdentity = 0;
 
    struct Vertex {
        Result value;
        MetaInformation meta;
        Vertex(Result v, MetaInformation m) : value(v), meta(m) {}
    };
 
    const ll seqSize;
    const ll treeSize;
    vector<Vertex> tree;
 
    // SegmentAdditionTree
 
    Result combine(Result a, Result b) {
        if (a.min < b.min)
            return a;
        if (b.min < a.min)
            return b;
        // return last
        return Result(a.min, max(a.pos, b.pos));
    }
 
    void metaUpdate(MetaInformation& toUpdate, MetaInformation by, ll left, ll right) {
        toUpdate += by;
    }
 
    Result metaApply(Result res, MetaInformation metaInfo, ll left, ll right) {
        res.min += metaInfo;
        return res;
    }
 
 
public:
 
    SegmentAdditionTree(vll& a)
        : seqSize(a.size()),
        treeSize(treeSizeFor(seqSize)),
        tree(2 * treeSize - 1, { identity, metaIdentity }) {
 
        for (ll i = 0; i < seqSize; ++i) {
            tree[treeSize - 1 + i].value = Result(a[i], i);
        }
        for (ll i = treeSize - 2; i >= 0; --i) {
            tree[i].value = combine(tree[leftSon(i)].value, tree[rightSon(i)].value);
        }
    }
 
    // [l, r]
    Result get(ll l, ll r) {
        return get(0, 0, treeSize - 1, l, r);
    }
 
    // [l, r]
    void update(ll l, ll r, MetaInformation meta) {
        update(0, 0, treeSize - 1, l, r, meta);
    }
 
    // [l, r]
    void update(ll pos, MetaInformation meta) {
        update(0, 0, treeSize - 1, pos, pos, meta);
    }
 
private:
    inline ll parent(ll v) { return (v - 1) >> 1; }
    inline ll leftSon(ll v) { return 2 * v + 1; }
    inline ll rightSon(ll v) { return 2 * v + 2; }
    inline ll midle(ll l, ll r) { return (l + r) >> 1; }
 
    static ll treeSizeFor(ll seqSize) {
        ll degree2 = 1;
        while (degree2 < seqSize)
            degree2 <<= 1;
        return degree2;
    }
 
    // push updates return value at root vertex and propagates
    // its meta info to its children in case they exist
    void push(ll parent, ll left, ll right) {
        //tree[parent].value = metaApply(tree[parent].value, tree[parent].meta, left, right);
        if (left != right) { // if not leaf
            auto meta = tree[parent].meta;
            ll mid = midle(left, right);
            metaUpdate(tree[leftSon(parent)].meta, meta, left, mid);
            metaUpdate(tree[rightSon(parent)].meta, meta, mid + 1, right);
            tree[parent].meta = metaIdentity;
        }
    }
 
    void updateValue(ll v, ll tl, ll tr) {
        ll tm = midle(tl, tr);
        tree[v].value = combine(
            metaApply(tree[leftSon(v)].value, tree[leftSon(v)].meta, tl, tm),
            metaApply(tree[rightSon(v)].value, tree[rightSon(v)].meta, tm + 1, tr)
        );
    }
 
    Result get(ll v, ll tl, ll tr, ll l, ll r) {
        if (tl == l && tr == r) {
            return metaApply(tree[v].value, tree[v].meta, tl, tr);
        }
 
        push(v, tl, tr);
        ll tm = midle(tl, tr);
        Result ans = identity;
        if (r <= tm) // [l, r] \in [tl, tm]
            ans = get(leftSon(v), tl, tm, l, r);
 
        else if (l >= tm + 1) // [l, r] \in [tm + 1, tr]
            ans = get(rightSon(v), tm + 1, tr, l, r);
        else {
            ans = combine(
                get(leftSon(v), tl, tm, l, min(tm, r)),
                get(rightSon(v), tm + 1, tr, max(tm + 1, l), r)
            );
        }
        updateValue(v, tl, tr);
        return ans;
    }
 
    void update(ll v, ll tl, ll tr, ll l, ll r, MetaInformation meta) {
        if (tl == l && tr == r) {
            metaUpdate(tree[v].meta, meta, tl, tr);
            return;
        }
 
        push(v, tl, tr);
        ll tm = midle(tl, tr);
        if (r <= tm) {
            update(leftSon(v), tl, tm, l, r, meta);
        }
        else if (l >= tm + 1) {
            update(rightSon(v), tm + 1, tr, l, r, meta);
        }
        else {
            update(leftSon(v), tl, tm, l, min(tm, r), meta);
            update(rightSon(v), tm + 1, tr, max(tm + 1, l), r, meta);
        }
        updateValue(v, tl, tr);
    }
};
 
 
int main()
{
 
    ll n;
    cin >> n;
    vll s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
 
    vll ans(n, -1);
   
    SegmentAdditionTree tree_(s);
    for (int i = 0; i < n; ++i) {
        auto r = tree_.get(0, n - 1);
        ans[r.pos] = i + 1;
        tree_.update(r.pos, r.pos, 1e16 + 239);
        if (r.pos + 1 <= n - 1) {
            tree_.update(r.pos + 1, n - 1, -(i + 1));
        }
    }
   
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
}