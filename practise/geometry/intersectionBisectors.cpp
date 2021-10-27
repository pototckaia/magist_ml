#include <iostream>
#include <cmath>

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

Point operator /(const Point& a, const double& k) {
    return Point(a.x / k, a.y / k);
}

double len(const Point& a) {
    return hypot(a.x, a.y);
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
    cin >> a >> b >> c;

    auto len1 = len(b - a);
    auto len2 = len(c - b);
    auto len3 = len(a - c);

    auto d = (a * len2 + b * len3 + c * len1) / (len1 + len2 + len3);

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
	cout << d;

    return 0;
}