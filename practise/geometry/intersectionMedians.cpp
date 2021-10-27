#include <iostream>

using namespace std;

struct Point {
    double x, y;
    Point(){}
    Point(double  x_, double  y_):x(x_), y(y_){}
};

Point operator -(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator +(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator *(const Point& a, const double& k) {
    return Point(a.x * k, a.y * k);
}

Point operator / (const Point& a, const double& k) {
    return Point(a.x / k, a.y / k);
}

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator <<(ostream& out, const Point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

int main() {
    Point a, b, c;
	// not in one line
    cin >> a >> b >> c;

    auto a1 = (b + c) / 2;
    auto m((a  + a1 * 2) / 3);

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
	cout << m;
	
    return 0;
}