#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const double EPS = 0.000000001;

int quadraticEquation(double A, double B, double C, double& point1, double& point2) {
	if (fabs(A) < EPS && fabs(B) < EPS) {
		return 0;
	}
	if(fabs(A) < EPS){
		point1 = -C / B;
		return 1;
	}

	long double D = B * B - 4 * A * C;
	if (D < 0.0){
		return 0;
	}
	if (fabs(D) < EPS){
		point1 = -B / (2 * A);
		return 1;
	}
	point1 = (-B - sqrt(D)) / (2 * A);
	point2 = (-B + sqrt(D)) / (2 * A);
	if(point2 < point1) {
		swap(point1, point2);
	}
	return 2;
}

struct Vector2D {
	Vector2D() = default;
	Vector2D(double x_, double y_) : x(x_), y(y_) {}
	double x, y;
};

double dot(Vector2D left, Vector2D right) {
	return left.x * right.x + left.y * right.y;
}

Vector2D operator+(Vector2D left, Vector2D right) {
	return Vector2D(left.x + right.x, left.y + right.y);
}

Vector2D operator*(Vector2D left, double scalar) {
	return Vector2D(left.x * scalar, left.y * scalar);
}

Vector2D operator-(Vector2D left, Vector2D right) {
	return Vector2D(left.x - right.x,left.y - right.y);
}

struct Line {
	Line(double a, double b, double c) {
		// y = - (c + ax) / b
		if (fabs(b) > EPS) {
			begin.x = 0;
			end.x = 1;
			begin.y = - (c + (a * begin.x)) / b;
			end.y = - (c + (a * end.x)) / b;
		}
		else {
			begin.x = -c / a;
			end.x = -c / a;
			begin.y = 0;
			begin.y = 1; 
		}
	}

	Vector2D begin, end;
};

vector<Vector2D> cross(Line line, Vector2D center, double r) {
	//p(t) = a + (b - a) * t - line
	// (p(t) - center) * (p(t) - center) = r * r - cycle
	// t*t * (b - a) * (b - a) + 2 * t * (b - a) * (a - c) + (a - c) * (a - c) - r * r = 0
	double point1, point2;
	auto type = quadraticEquation(
		dot(line.end - line.begin, line.end - line.begin), 
		2 * dot(line.end - line.begin,line.begin - center), 
		dot(line.begin - center, line.begin - center) - r * r,
		point1, point2);

	vector<Vector2D> result;
	if (type == 1) {
		result.push_back(line.begin +  (line.end - line.begin) * point1);
	} else if (type == 2) {
		result.push_back(line.begin + (line.end - line.begin) * point1);
		result.push_back(line.begin + (line.end - line.begin) * point2);
	}
	return result;
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
	int m; cin >> m;
	cout << fixed << setprecision(8);
	for (int i = 0; i < m; ++i) {
		Vector2D center1, center2;
		double r1, r2;
		cin >> center1.x >> center1.y >> r1;
		cin >> center2.x >> center2.y >> r2;

		if (fabs(center1.x - center2.x) < EPS && fabs(center1.y - center2.y) < EPS) {
			cout << (fabs(r2 - r1) < EPS ? -1 : 0) << endl;
			continue;
		}

		center2 = center2 - center1;
		
		Line line(-2 * center2.x, 
			-2 * center2.y, 
			center2.x * center2.x + center2.y * center2.y + r1 * r1 - r2 * r2);
		auto dots = cross(line, center2, r2);
		cout << dots.size() << endl;
		std::sort(dots.begin(), dots.end(), [](auto& left, auto& right) {
			return (left.x < right.x) ? true : (left.x > right.x) ? false : (left.y < right.y);
		});
		for (auto d: dots) {
			cout << center1.x + d.x << endl << center1.y + d.y << endl;
		}
	}
}
