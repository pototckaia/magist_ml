#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using ll = std::int64_t;
using ull = std::uint64_t;
using ui = std::uint32_t;
using vll = std::vector<ll>;
using namespace std;

#define rep(i, a, b) for (ll (i) = (a); (i) < (b); ++(i))

void compressionCoord(vector<ui>& coords) {
	sort(coords.begin(), coords.end());
	coords.erase(unique(coords.begin (), coords.end()), coords.end());

}

ui getCoordIntex(vector<ui>& coords, ui value) {
	return lower_bound(coords.begin(), coords.end(), value) - coords.begin();
}


int main() {

}