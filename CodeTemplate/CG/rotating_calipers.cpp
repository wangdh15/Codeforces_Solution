/**
 *https://www.acwing.com/problem/content/description/2941/
 *
 *
 */

#include <iostream>
#include <algorithm>

using namespace std;

class Point {
public:
    int x, y;
    explicit Point(int _x=0, int _y=0): x(_x), y(_y) {}
    bool operator<(const Point &rhs) const {
        return x < rhs.x || x == rhs.x && y < rhs.y;
    }
    Point operator-(const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    int operator^(const Point &rhs) const {
        return x * rhs.y - y * rhs.x;
    }
    int get_dis() const {
        return x * x + y * y;
    }
    friend ostream& operator<<(ostream &os, const Point &p) {
        os << p.x << ' ' << p.y << endl;
    }
};

typedef Point Vector;

class Line{
public:
    Point p;
    Vector v;
    Line(const Point &_p, const Vector &_v) : p(_p), v(_v) {}
    Line() = default;
};


int to_left_test(const Line &l, const Point p) {
    
    return (l.v ^ (p - l.p));
    
}

// 得到a, b, c三个点构成的三角形的有向面积
double get_area(const Point &a, const Point &b, const Point &c) {
    return (b - a) ^ (c - a);
}

const int N = 5e4 + 5;

// andrew算法求凸包
Point p[N];
int n;
int stk[N], top;  // 最终stk中按照逆时针存储凸包上的所有点
bool used[N];

void andrew() {
    sort(p, p + n);
    for (int i = 0; i < n; i ++) {
        while (top >= 2 && to_left_test(Line(p[stk[top]], p[stk[top]] - p[stk[top - 1]]), p[i]) <= 0) {  // 按照题目要求，在边界上的点是否保留，如果保留，则改成 <
            if (to_left_test(Line(p[stk[top]], p[stk[top]] - p[stk[top - 1]]), p[i]) < 0) { // 在边界上的点used还要是true，不然有相同点的时候会出问题
                used[stk[top]] = false;
            }
            top --;
        }
        stk[++ top] = i;
        used[i] = true;
    }

    used[0] = false; // 将起点再置为false，求上半部分的时候再加入

    for (int i = n - 1; i >= 0; i --) {
        if (used[i]) continue;
        while (top >= 2 &&to_left_test(Line(p[stk[top]], p[stk[top]] - p[stk[top - 1]]), p[i]) <= 0) { // 按照题目要求，在边界上的点是否保留，如果保留，则改成 <
            if (to_left_test(Line(p[stk[top]], p[stk[top]] - p[stk[top - 1]]), p[i]) < 0) { // 在边界上的点used也要置为true，不然出现相同的点会有问题
                used[stk[top]] = false;
            }
            top --;
        }
        stk[++ top] = i;
        used[i] = true;
    }
    top --;
}

// andrew算法求凸包
// END


// 旋转卡壳BEGIN
int rotating_calipers() {
    
    vector<int> t(top);
    for (int i = 0; i < top; i ++) t[i] = stk[i + 1];
    if (top <= 2) return (p[0] - p[n - 1]).get_dis();
    int ans = 0;
    int j = 2;
    for (int i = 0; i < top; i ++) {
        auto st = p[t[i]], en = p[t[(i + 1) % top]];
        while (get_area(st, en, p[t[j]]) < get_area(st, en, p[t[(j + 1) % top]])) j = (j + 1) % top;
        ans = max(ans, (st - p[t[j]]).get_dis());
    }
    return ans;
}
// 旋转卡壳结束


int main() {
    
    
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        p[i] = Point(x, y);
    }
    
    andrew();
    cout << rotating_calipers();
    return 0;
    
}
