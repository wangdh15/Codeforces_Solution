#include <iostream>
#include <cmath>

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

};

typedef Point Vector;

/**
 * 得到两个直线的交点坐标
 * @param p 第一个直线上的点
 * @param v 第一个直线的方向向量
 * @param q 第二个直线上的点
 * @param w 第二个直线的方向向量
 * @return 交点
 */
Point get_line_intersection(const Point &p, const Vector &v, const Point &q, const Vector &w) {
    Vector u = p - q;
    double t = (w ^ u) / (v ^ w);
    return p + v * t;
}

/**
 * 点到直线的距离
 * @param A 直线外一点
 * @param P 直线上一点
 * @param v 直线的方向向量
 * @return
 */
double point_line_distance(const Point &A, const Point &P, const Vector &v) {
    return fabs((A - P) ^ v) / v.getLength();
}

/**
 * 点到线段的距离
 * @param P 线段外的点
 * @param A 线段的两个端点
 * @param B 线段的两个端点
 * @return
 */
double point_segment_distance(const Point &P, const Point &A, const Point &B) {
    if (A == B) return (P - A).getLength();
    Vector ab = B - A, ap = P - A, bp = P - B;
    if (sign(ab * ap) < 0) return ap.getLength();
    if (sign(ab * bp) > 0) return bp.getLength();
    return point_line_distance(P, A, A - B);
}

/**
 * 得到点P在直线上的投影的点
 * @param P 要投影的点
 * @param A 被投影的直线
 * @param v
 * @return
 */
Point get_line_projection(const Point &P, const Point &A, const Vector &v) {
    return A + v * (((P - A) * v) / (v * v));
}

/**
 * 判断点P是否在线段AB上，也可以用点到线段的距离来判断
 * @param P
 * @param A
 * @param B
 * @return
 */
bool point_on_segment(const Point &P, const Point &A, const Point &B) {
    Vector ap = P - A, bp = P - B;
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