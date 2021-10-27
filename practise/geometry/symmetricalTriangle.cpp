#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using ll = int64_t;

struct Point {
    ll x, y;
    Point(){}
    Point(int x_, int y_):x(x_), y(y_){}
};

Point operator *(const Point& a, const int k) {
    return Point(a.x * k, a.y * k);
}

istream& operator >>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator <<(ostream& out, const Point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

bool operator ==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p2.y == p1.y;
}

inline ll triangle_area (Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool bounding_box (int a, int b, int c, int d) {
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    return max(a,c) <= min(b,d);
}

int sgn(ll val) {
    return (0 < val) - (val < 0);
}

bool intersect (Point&  a, Point& b, Point& c, Point& d) {
    return bounding_box(a.x, b.x, c.x, d.x)
        && bounding_box(a.y, b.y, c.y, d.y)
        && sgn(triangle_area(a,b,c)) * sgn(triangle_area(a,b,d)) <= 0
        && sgn(triangle_area(c,d,a)) * sgn(triangle_area(c,d,b)) <= 0;
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
	
    Point a, b, d; cin >> a >> b >> d;
	
    auto a1 =  a * (-1);
	auto b1 = b * (-1);
	auto d1 = d * (-1);

	if (intersect(a, b, a1, b1) || intersect(a, b, a1, d1) || intersect(a, b, d1, b1) ||
        intersect(a, d, a1, b1) || intersect(a, d, a1, d1) || intersect(a, d, d1, b1) ||
        intersect(d, b, a1, b1) || intersect(d, b, a1, d1) || intersect(d, b, d1, b1)) {
		cout << 987654321;
	}
    else {
	    cout << a1 << " " << b1 <<  " " << d1;
    }
	
    return 0;
}