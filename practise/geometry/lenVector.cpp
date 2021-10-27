#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(7);
    cout << hypot(x1 - x0, y1 - y0);
    return 0;
}