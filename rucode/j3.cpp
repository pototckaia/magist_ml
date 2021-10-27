#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

using ll = long long;

struct Vector2D {
	ll x, y;
	Vector2D(){}
	Vector2D(ll  x_, ll y_):x(x_), y(y_){}
};

Vector2D operator -(const Vector2D& a, const Vector2D& b) {
	return Vector2D(a.x - b.x, a.y - b.y);
}

ll cross(const Vector2D& a, const Vector2D& b) {
	return a.x * b.y - a.y * b.x;
}

ll dot(const Vector2D& a, const Vector2D& b) {
	return a.x * b.x + a.y * b.y;
}

istream& operator >>(istream& in, Vector2D& p) {
	in >> p.x >> p.y;
	return in;
}

ofstream& operator <<(ofstream& out, Vector2D& p) {
	out << p.x << " " << p.y;
	return out;
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

	Vector2D a, b, c, d;
	cin >> a >> b >> c >> d;

	auto ab = b - a;
	auto cd = d -  c;
	if (cross(ab, cd) == 0) {
		if (cross(cd, a  - c) == 0 && cross(cd, b - c) == 0) {
			cout << 2;
		}
		else {
			cout << 0;
		}
	}
	else {
		auto n = Vector2D(-cd.y, cd.x);
		double t = static_cast<double>(dot(n, c - a)) / dot(n, ab);
		cout << "1 " << a.x + ab.x * t << " " << a.y + ab.y * t;
	}

	return 0;
}
// Yes NO