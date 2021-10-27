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
     
    int main(int argc, char* argv[]) {	
    #ifdef _DEBUG
        ios_base::sync_with_stdio(false);
        ifstream in(infile);
        ofstream out(outfile);
        cin.rdbuf(in.rdbuf());
        cout.rdbuf(out.rdbuf());
    #endif
     
    	ll n, k; cin >> n >> k;
    	vector<ll> ar(n);
    	rep(i, 0, n) { cin >> ar[i]; }
     
    	rep(_, 0, k) {
    		ll C; cin >> C;
     
    		ll left(-1), right(n);
    		while (right - left > 1) {
    			ll mid((left + right)/2);
    			if (ar[mid] >= C) {
    				right = mid;
    			} else {
    				left = mid;
    			}
    		}
    		cout << right + 1 << endl;
    	}
        
    }