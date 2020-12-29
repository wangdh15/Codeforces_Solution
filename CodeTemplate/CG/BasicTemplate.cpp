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

    Point(double _x=0, double _y=0) : x(_x), y(_y) {}

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
    Point operator*(double b) {
        return Point(x * b, y * b);
    }

    /**
     * 重载数量除操作
     * @param b
     * @return
     */
    Point operator/(double b) {
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
