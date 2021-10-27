#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    Point(){}
};

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

inline int triangle_area (Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool bounding_box (int a, int b, int c, int d) {
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    return max(a,c) <= min(b,d);
}

bool intersect (Point&  a, Point& b, Point& c, Point& d) {
    return bounding_box(a.x, b.x, c.x, d.x)
        && bounding_box(a.y, b.y, c.y, d.y)
        && triangle_area(a,b,c) * triangle_area(a,b,d) <= 0
        && triangle_area(c,d,a) * triangle_area(c,d,b) <= 0;
}

int main() {
    Point a, b, c, d;
    cin >> a >> b >> c >> d;

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(8);
    if (intersect(a, b, c , d)) {
        cout << "YES";
    }
    else
        cout << "NO";
    return 0;
}