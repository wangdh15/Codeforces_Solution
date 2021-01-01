/**
 *
 * https://www.acwing.com/problem/content/3072/
 *
 */

#include <iostream>
#include <cmath>
using namespace std;

double a, b, c, d, l, r;

const double eps = 1e-12;

double f(double x) {

    return (c * x + d) / (a * x + b);

}

double simpson(double l, double r) {
    auto mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}


double ars(double l, double r, double s) {
    auto mid = (l + r) / 2;
    auto left = simpson(l, mid), right = simpson(mid, r);
    if (fabs(left + right - s) < eps) return s;
    return ars(l, mid, left) + ars(mid, r, right);
}


int main() {


    cin >> a >> b >> c >> d >> l >> r;

    printf("%.6lf", ars(l, r, simpson(l, r)));
    return 0;

}
