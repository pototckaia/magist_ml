#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
    Point(){}
    Point(int x_, int y_):x(x_), y(y_){}
};

int dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

double len(const Point& a) {
    return hypot(a.x, a.y);
}

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int main() {
    Point a, b;
    cin >> a >> b;

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
    cout << acos(dot(a, b) / len(a) / len(b));
    return 0;
}