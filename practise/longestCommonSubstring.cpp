#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <string>
#include <map>
#include <algorithm>

#define _DEBUG
std::string infile = "input.txt";
std::string outfile = "output.txt";

using namespace std;

int main(int argc, char* argv[]) {

#ifdef _DEBUG
    ios_base::sync_with_stdio(false);
    ifstream in(infile);
    ofstream out(outfile);
    cin.rdbuf(in.rdbuf());
    cout.rdbuf(out.rdbuf());
#endif
    std::string a, b;
    cin >> a >> b;

    std::vector<std::vector<int>> lcs(a.size() + 1, std::vector<int>(b.size() + 1, 0));

	int stra = a.size(), strb = b.size();
	for (int i = 1; i <= stra; ++i) {
		for (int j = 1; j <= strb; ++j) {
			if (a[i - 1] == b[j - 1]) {
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			}
		}
	}

	int u(0), v(0), len(0);
	for (int i = 0; i <= stra; ++i) {
		for (int j = 0; j <= strb; ++j) {
			if (lcs[i][j] > len) {
				len = lcs[i][j];
				u = i; v = j;
			}
		}
	}

	for (int i = u - len; i < u; ++i) {
		cout << a[i];
	}
}
