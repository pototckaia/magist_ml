#include <iostream>
#include <cmath>
#include <vector>

using ll = long long;
using namespace std;

struct Point {
    double x, y;
    Point(){}
    Point(double  x_, double  y_):x(x_), y(y_){}
};

int cross(Point& a, Point& b) {
	return a.x * b.y - b.x * a.y;
}

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int main() {
    int n; cin >> n;
    // simple polygon - vert in polygon in either clockwise or counterclockwise order.
    vector<Point> p(n);
    for (int i = 0; i < n; ++i) { cin >> p[i]; }

    ll square(0);
    for (int i = 0; i < n; ++i) {
        square += cross(p[i], p[(i + 1) % n]);
    }
    square = abs(square);

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(7);
    cout << static_cast<double>(square) / 2.0 << endl;

	return 0;
}