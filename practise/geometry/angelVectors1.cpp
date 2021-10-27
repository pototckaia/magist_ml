#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
    double x, y;
    Point(){}
    Point(double  x_, double  y_):x(x_), y(y_){}
};

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator <<(ostream& out, const Point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

double sq (const vector<Point> & fig) {
    double res = 0;
    for (unsigned i = 1; i <= fig.size(); ++i) {
        auto& p1 = fig[i - 1];
        auto& p2 = fig[i % fig.size()];
        res += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return fabs (res) / 2;
}

int main() {
    int n; cin >> n;

	vector<Point> p(n);
    for (int i = 0; i < n; ++i) { cin >> p[i]; }

	cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
    cout << sq(p);

    return 0;
}