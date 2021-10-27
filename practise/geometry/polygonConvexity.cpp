#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

using ll = long long;

struct Point {
	ll x, y;
	Point(){}
	Point(ll  x_, ll y_):x(x_), y(y_){}
};

Point operator -(const Point& a, const Point& b) {
	return Point(a.x - b.x, a.y - b.y);
}

ll cross(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

istream& operator >>(istream& in, Point& p) {
	in >> p.x >> p.y;
	return in;
}

double S(Point& a, Point&p, Point& b) {
	return abs(cross(a - p, b - p)) / 2.0;
}

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

	ll n; cin >> n;
	vector<Point> p(n);
	for (int i = 0; i < n; ++i) { cin >> p[i]; }

	long long pos(0), neg(0);
	for (int i = 0; i < n; ++i) {
		ll cp = cross(p[(i + 1) %n] - p[i], p[i] - p[(i - 1 + n) % n]);
		if (cp > 0) {
			++pos;
		} else if (cp < 0) {
			++neg;
		}
	}

	if (pos == 0 ||  neg == 0) {
		cout << "Yes";
	} else {
		cout << "No";
	}

	return 0;
}
// Yes NO