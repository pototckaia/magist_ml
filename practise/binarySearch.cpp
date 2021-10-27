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
     
    ll lower_bound(vector<ll>& a, ll value) {
    	ll left(-1), right(a.size());
    	while (right - left > 1) {
    		ll mid((left + right)/2);
    		if (a[mid] >= value) {
    			right = mid;
    		} else {
    			left = mid;
    		}
    	}
    	return right;
    }
     
    ll upper_bound(vector<ll>& a, ll value) {
    	ll left(-1), right(a.size());
    	while (right - left > 1) {
    		ll mid((left + right)/2);
    		if (a[mid] > value) {
    			right = mid;
    		} else {
    			left = mid;
    		}
    	}
    	return right;
    }
     
    int main(int argc, char* argv[]) {	
    #ifdef _DEBUG
        ios_base::sync_with_stdio(false);
        ifstream in(infile);
        ofstream out(outfile);
        cin.rdbuf(in.rdbuf());
        cout.rdbuf(out.rdbuf());
    #endif
     
    	ll n; cin >> n;
    	vector<ll> a(n);
    	rep(i, 0, n) { cin >> a[i]; }
    	sort(a.begin(), a.end());
    	
    	ll k; cin >> k;
    	rep(_, 0, k) {
    		ll l, r; cin >> l >> r;
    		// ������� ����� ����� �������� �� l �� r
     
    		auto left(lower_bound(a, l));
    		auto right(upper_bound(a, r));
    		cout << right - left << endl;	
    	}
        
    }