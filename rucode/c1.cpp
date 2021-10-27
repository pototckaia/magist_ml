#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

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

   std::string p, s;
   std::getline(cin, p);
   std::getline(cin, s);

	vector<char> ors(p.size() + 1);
	ors[0] = 1;

	vector<vector<int>> d(s.size() + 1, vector<int>(p.size() + 1));
	d[0][0] = 1;


	for (int j = 1; j <= p.size(); ++j) {
        d[0][j] = p[j - 1] == '*' ? ors[j - 1] : 0;
        ors[j] |= d[0][j];
    }

    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= p.size(); ++j) {
            d[i][j] = p[j - 1] == '*' ? ors[j - 1] :
                (p[j - 1] == '?' || p[j - 1] == s[i - 1]) && d[i - 1][j - 1];
            ors[j] |= d[i][j];
        }
    }

    if (d[s.size()][p.size()]) {
		cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}