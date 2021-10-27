#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#define rep(i, start, end) for (auto i(start); (i) < (end); ++(i))
#define rep_d(i, start, end) for (auto i(start); (i) >= (end); --(i))

std::string infile = "input.txt";
std::string outfile = "output.txt";

using uns = unsigned;
using ull = unsigned long long;
using ll = long long;

using namespace std;

void counterSort(vector<ll>& arr, vector<ll>& param) {
    ll n(arr.size());
    vector<ll> cnt(n), ans(n);
    rep(i, 0, n) {
        cnt[param[i]]++;
    }
    ll acc(0);
    rep(i, 0, n) {
        ll tmp(cnt[i]);
        cnt[i] = acc;
        acc += tmp;
    }
    rep(i, 0, n) {
        ll index(param[arr[i]]);
        ans[cnt[index]] = arr[i];
        ++cnt[index];
    }
    arr = ans;
}

vector<ll> createSuffixArray(const string& s, vector<ll>& posSuffixArray) {
    string text(s + "$");
    ll n(text.size());
    vector<ll> suffixArray(n), equivalent(n);

    rep(i, 0, n) {  suffixArray[i] = i; }
    sort(suffixArray.begin(), suffixArray.end(), [&](auto x, auto y) { return text[x] < text[y]; });
    rep(i, 1, n) {
        auto increase(text[suffixArray[i - 1]] != text[suffixArray[i]]);
        equivalent[suffixArray[i]] = equivalent[suffixArray[i - 1]] + increase;
    }
    vector<ll> new_equivalent(n);
    for (ll degree(1); degree < n; degree <<= 1) {
        rep(i, 0, n) { 
            suffixArray[i] = (suffixArray[i] - degree + n) % n;
        }
        counterSort(suffixArray, equivalent);

        new_equivalent[0] = 0;
        rep(i, 1, n) {
            pair<ll, ll> now{equivalent[suffixArray[i]], equivalent[(suffixArray[i] + degree) % n]};
            pair<ll, ll> prev{equivalent[suffixArray[i-1]], equivalent[(suffixArray[i-1] + degree) % n]};

            new_equivalent[suffixArray[i]] = new_equivalent[suffixArray[i - 1]] + ll(now != prev);
        }
        equivalent = new_equivalent;
    }
    posSuffixArray = equivalent;
    return suffixArray;
}

int main(int argc, char* argv[]) {	
#ifdef _DEBUG
    ios_base::sync_with_stdio(false);
    ifstream in(infile);
    ofstream out(outfile);
    cin.rdbuf(in.rdbuf());
    cout.rdbuf(out.rdbuf());
#endif

    string text; cin >> text;

    vector<ll> posSuffixArray;
    auto suffixArray(createSuffixArray(text, posSuffixArray));

    ll k(0);
    vector<ll> lcp(suffixArray.size());
    rep(i, 0ll, text.size() - 1ll) {
        ll j(suffixArray[posSuffixArray[i] - 1]);
        while (text[i + k] == text[j + k]) { ++k; }
        lcp[posSuffixArray[i]] = k;
        k = max(0ll, k - 1);
    }

    ll ans(0);
    rep(i, 1, suffixArray.size()) {
        ans += text.size() - suffixArray[i] - lcp[i];
    }
    cout << ans;
}
