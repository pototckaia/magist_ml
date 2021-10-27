#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    Point(){}
    Point(double  x_, double  y_):x(x_), y(y_){}
};

struct Line {
    double a, b, c;
    Line(Point u, Point v);
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

int dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

int cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double len(const Point& a) {
    return hypot(a.x, a.y);
}

double angle(const Point& a, const Point& b) {
    return atan2(cross(a, b), dot(a, b));
}


istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

Point normalized(const Point& a) {
    return a / len(a);
}

Point normal(const Point& a) {
	return normalized(Point(-a.y, a.x));
}

Point normal(const Line& a) {
	return normalized(Point(a.a, a.b));
}

Line::Line(Point u, Point v) {
    auto norm = normal(v - u);
    a = norm.x;
    b = norm.y;
    c = -(a * u.x + b * u.y);
};

ostream& operator <<(ostream& out, const Point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

int main() {
	Point a, b, c;
	cin >> a >> b >> c;
	
	auto a1 = (b + c) / 2;

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);

    auto m((a  + a1 * 2) / 3);
	cout << m;
	return 0;
}