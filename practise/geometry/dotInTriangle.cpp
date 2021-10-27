#include <iostream>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Point {
	int x, y;
	Point(){}
	Point(int  x_, int y_):x(x_), y(y_){}
};

Point operator -(const Point& a, const Point& b) {
	return Point(a.x - b.x, a.y - b.y);
}

int cross(const Point& a, const Point& b) {
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

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(8);

	const double eps = 1e-8;

	Point a, b, c, p;
	cin >> a >> b >> c >> p;

	auto all1(S(a, b, c));
	auto all2(S(a, b, p) + S(b, c, p) + S(a, p, c));

	if (fabs(all1 - all2) < eps) {
		cout << "In";
	}
	else
		cout << "Out";

	return 0;
}