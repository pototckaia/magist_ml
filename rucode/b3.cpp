#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
    Point(){}
    Point(int x_, int y_):x(x_), y(y_){}
};

Point operator -(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator +(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator *(const Point& a, const int& k) {
    return Point(a.x * k, a.y * k);
}

int dp(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

int cp(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double len(const Point& a) {
    return hypot(a.x, a.y);
}

double angle(const Point& a, const Point& b) {
    return atan2(cp(a, b), dp(a, b));
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
	Point a, b;
	cin >> a >> b;
	
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
	cout << acos(dp(a, b) / len(a) / len(b));
	return 0;
}