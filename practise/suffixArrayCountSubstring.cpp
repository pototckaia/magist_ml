#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#define rep(i, start, end) for (auto i(start); i < end; ++i)
#define rep_d(i, start, end) for (auto i(start); i >= end; --i)

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

vector<ll> createSuffixArray(const string& s) {
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
    return suffixArray;
}

ll binSearch(vector<ll>& suffixArray, string& pattern, string& text, bool isLeftSearch) {
    ll left = -1, right = suffixArray.size();
    while (right - left > 1) {
        ll mid((left + right) / 2);
        auto suffix(text.substr(suffixArray[mid], pattern.size()));
        if ((isLeftSearch && suffix >= pattern) || 
            (!isLeftSearch && suffix > pattern)) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    return isLeftSearch ? right : left;
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
    auto suffixArray(createSuffixArray(text));

    int n; cin >> n;
    rep(i, 0, n) {
        string pattern; cin >> pattern;
        ll leftBound(binSearch(suffixArray, pattern, text, true));
        ll rightBound(binSearch(suffixArray, pattern, text, false));
        if (leftBound > 0 && leftBound < suffixArray.size() && 
            rightBound > 0 && rightBound < suffixArray.size() && 
            text.substr(suffixArray[leftBound], pattern.size()) == pattern) {
            cout << rightBound - leftBound + 1<< endl;
        } else {
            cout << 0 << endl;
        }
    }

}
