#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

using ll = std::int64_t;

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

    int n; cin >> n;
	vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = 0, t = -1;
    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1]) {
            ++ans;
        }
        else if (t != (a[i] - a[i - 1] > 0)) {
            t = a[i] - a[i - 1] > 0;
        }
    	else {
            ++ans;
        }
    }
    cout << ans;
    return 0;
}
