#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long LL;

// 定义PI以及精度
const double PI = acos(-1), eps = 1e-8;

/**
 * 符号函数，判断x的符号
 * @param x
 * @return
 */
int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

/**
 * 比较两个数的大小， 0表示相同，-1表示x小于y， 1 表示x大于y
 * @param x
 * @param y
 * @return
 */
int cmp(double x, double y) {
    return sign(x - y);
}

/**
 * 点类和向量类
 */
class Point{
public:

    double x, y;

    explicit Point(double _x=0, double _y=0) : x(_x), y(_y) {}

    /**
     * 重载减法
     * @param rhs
     * @return
     */
    Point operator-(const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }

    /**
     * 重载加法
     * @param rhs
     * @return
     */
    Point operator+(const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }


    /**
  * 重载数量乘操作
  * @param b
  * @return
  */
    Point operator*(double b) const {
        return Point(x * b, y * b);
    }

    /**
     * 重载数量除操作
     * @param b
     * @return
     */
    Point operator/(double b) const {
        return Point(x / b, y / b);
    }

    /**
     * 内积
     * @param rhs
     * @return
     */
    double operator*(const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    /**
     * 叉积
     * @param rhs
     * @return
     */
    double operator^(const Point &rhs) const {
        return x * rhs.y - rhs.x * y;
    }

    /**
     * 重载==操作符，判断两个点是否相同
     * @param rhs
     * @return
     */
    bool operator==(const Point &rhs) const{
        return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0;
    }

    /**
     * 重载比较操作符
     * @param rhs
     * @return
     */
    bool operator<(const Point &rhs) const {
        return cmp(x, rhs.x) < 0 || cmp(x, rhs.x) == 0 && cmp(y, rhs.y) < 0;
    }

    /**
     * 求向量模长
     * @return
     */
    double getLength() const {
        return sqrt(*this * *this);
    }


    /**
     * 输出函数，Debug用
     * @param os
     * @param rhs
     * @return
     */
    friend ostream& operator<<(ostream& os, const Point &rhs) {
        os << "Point: " << rhs.x << ' ' << rhs.y << endl;
        return os;
    }

    /**
     * 返回两条直线的夹角
     * @param a
     * @param b
     * @return
     */
    friend double getAngle(const Point &a, const Point &b) {
        return acos(a * b / a.getLength() / b.getLength());
    }

    /**
     * 返回当前向量逆时针旋转angle角度的向量
     * @param angle
     * @return
     */
    Point rotate(double angle) {
        return Point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }

    /**
     * 求单位长度的法向量
     * @return
     */
    Point getNormalVector() const {
        double len = getLength();
        return Point(- y / len, x / len);
    }

    /**
     * 求直线的角度，范围是-pi ~ pi
     * @return
     */
    double angle() const {
        return atan2(y, x);
    }

};

typedef Point Vector;

/**
 * 直线类
 */
class Line {
public:
    Point p;  // 直线上的一个点
    Vector v; // 指向的方向向量
    Line() = default;
    Line(const Point &_p, const Vector _v) : p(_p), v(_v) {}
};

/**
 * 得到两个直线的交点
 * @param l1
 * @param l2
 * @return
 */
Point get_line_intersection(const Line &l1, const Line &l2) {
    Vector u = l1.p - l2.p;
    double t = (l2.v ^ u) / (l1.v ^ l2.v);
    return l1.p + l1.v * t;
}

/**
 * 点到直线的距离
 * @param l 直线
 * @param p 点
 * @return
 */
double point_line_distance(const Line &l, const Point &p) {
    return fabs((p - l.p) ^ l.v) / l.v.getLength();
}

/**
 * 线段类
 */
class Segment{
public:
    Point st, en;  // 线段的两个端点
    Segment() = default;
    Segment(const Point &_st, const Point &_en) : st(_st), en(_en) {}
};

/**
 * 点到线段的距离
 * @param seg 线段
 * @param p 点
 * @return
 */
double point_segment_distance(const Segment &seg, const Point &p) {
    if (seg.en == seg.en) return (seg.st - p).getLength();
    Vector ab = seg.en - seg.st, ap = p - seg.st, bp = p - seg.en;
    if (sign(ab * ap) < 0) return ap.getLength();
    if (sign(ab * bp) > 0) return bp.getLength();
    Line t = Line(seg.st, seg.en - seg.st);
    return point_line_distance(t, p);
}


/**
 * 得到点p在直线l上的投影
 * @param l 直线
 * @param p 点
 * @return
 */
Point get_line_projection(const Line &l, const Point &p) {
    return l.p + l.v * (((p - l.p) * l.v) / (l.v * l.v));
}

/**
 * 判断点p是否在线段seg上
 * @param seg
 * @param p
 * @return
 */
bool point_on_segment(const Segment &seg, const Point &p) {
    Vector ap = p - seg.st, bp = p - seg.en;
    return sign(ap ^ bp) == 0 && sign(ap * bp) <= 0;
}

/**
 * 判断线段A1A2 和线段B1B2是否相交
 * @param A1
 * @param A2
 * @param B1
 * @param B2
 * @return
 */
bool segment_insection(const Point &A1, const Point &A2, const Point &B1, const Point &B2) {
    Vector a1a2 = A2 - A1, a1b1 = B1 - A1, a1b2 = B2 - A1;
    Vector b1b2 = B2 - B1, b1a1 = A1 - B1, b1a2 = A2 - B1;
    return sign(a1a2 ^ a1b1) * sign(a1a2 ^ a1b2) <= 0 && sign(b1b2 ^ b1a1) * sign(b1b2 ^ b1a2) <= 0;
}

bool segment_insection(const Segment &seg1, const Segment &seg2) {
    Vector a1a2 = seg1.en - seg1.st, a1b1 = seg2.st - seg1.st, a1b2 = seg2.en - seg1.st;
    Vector b1b2 = seg2.en - seg1.st, b1a1 = seg1.st - seg2.st, b1a2 = seg1.en - seg2.st;
    return sign(a1a2 ^ a1b1) * sign(a1a2 ^ a1b2) <= 0 && sign(b1b2 ^ b1a1) * sign(b1b2 ^ b1a2) <= 0;
}

/**
 * 求多边形的面积，p是按照多边形逆时针存的点
 * @param p
 * @param n
 * @return
 */
double polygon_area(const Point p[], int n) {
    double s = 0;
    for (int i = 1; i + 1 < n; i ++) {
        s += (p[i] - p[0]) ^ (p[i + 1] - p[i]);
    }
    return s / 2;
}

/**
 * 判断点p是否在直线l的左侧
 * @param l
 * @param p
 * @return
 */
int to_left_test(const Line &l, const Point &p) {
    return sign(l.v ^ (p - l.p));
}

// andrew算法求凸包
const int N = 1e4 + 5;
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
}

// andrew算法求凸包
// END

int main() {

    cin >> n;
    for (int i = 0; i < n; i ++) {
        double x, y;
        cin >> x >> y;
        p[i] = Point(x, y);
    }

    andrew();
    double ans = 0;
    for (int i = 2; i <= top; i ++) {
        ans += (p[stk[i]] - p[stk[i - 1]]).getLength();
    }
    printf("%.2lf", ans);
    return 0;
}
