#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

using ll = std::int64_t;
using ull = std::uint64_t;
using ui = std::uint32_t;
using vll = std::vector<ll>;
using namespace std;

#define rep(i, a, b) for (ll (i) = (a); (i) < (b); ++(i))

double distance(std::string& a, std::string& b, vector<double>& freequency) {
	if (a.size() > b.size()) {
		return distance(b, a, freequency);
	}

	static double dp[2][1005];
	ll currentRow = 0, prevRow = 1;
	dp[0][0] = dp[1][0] = 0;
	for (int i = 1; i < static_cast<int>(a.size()) + 1; ++i) {
		dp[currentRow][i] = dp[currentRow][i - 1] + freequency[a[i - 1] - 'A'];
	}

	for (int i = 1; i < static_cast<int>(b.size()) + 1; ++i) {
		auto deleteCost = freequency[b[i - 1] - 'A'];
		std::swap(prevRow, currentRow);
		dp[currentRow][0] += deleteCost;
		for (auto k = 1; k < static_cast<int>(a.size()) + 1; ++k) {
			dp[currentRow][k] = 0;
		}
		
		for (int j = 1; j < static_cast<int>(a.size()) + 1; ++j) {
			auto insertCost = freequency[a[j - 1] - 'A'];
			auto replaceCost = insertCost + deleteCost;

			auto replace = dp[prevRow][j - 1];
			if (a[j - 1] != b[i - 1]) {
				replace += replaceCost;
			}

			dp[currentRow][j] = std::min( {
				dp[currentRow][j - 1] + insertCost,
				dp[prevRow][j] + deleteCost,
				replace
			});
		}
	}
	return dp[currentRow][a.size()];
}


int main() {
	//#ifdef _DEBUG
	std::string infile = "input.txt";
	std::string outfile = "output.txt";
	ios_base::sync_with_stdio(false);
	ifstream in(infile);
	ofstream out(outfile);
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
	//#endif

	std::vector<std::string> data;
	for (std::string line; std::getline(cin, line);) {
		data.emplace_back(line);
	}
	vector<double> freequency('Z' - 'A', 0.0);
	ll size = 0;
	for (auto& line: data) {
		for (auto amino: line) {
			freequency[amino - 'A'] += 1;
			size += 1;
		}
	}
	for (auto& amino: freequency) {
		amino /= size;
	}



	double minDist = std::numeric_limits<double>::max();
	int minI = -1, minJ = -1;
	for (int i = 0; i < static_cast<int>(data.size()); ++i) {
		for (int j = i + 1; j < static_cast<int>(data.size()); ++j) {
			auto m = distance(data[i], data[j], freequency);
			if (m < minDist) {
				minDist = m;
				minI = i;
				minJ = j;
			}
		}
	}

	cout << minI + 1 << " " << minJ + 1 << " " << fixed << std::setprecision(2) << minDist;
}
