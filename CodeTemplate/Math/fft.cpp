/**
 * https://www.acwing.com/problem/content/description/3125/
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 300010;
const double PI = acos(-1);

int n, m;
struct Complex
{
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
}a[N], b[N], w[N];
int rev[N], bit, tot;

void fft(Complex a[], int inv)
{
  	// 将信号放到对应的位置
    for (int i = 0; i < tot; i ++ )
        if (i < rev[i])  // 只能交换一次
            swap(a[i], a[rev[i]]);  
    w[0] = Complex({1, 0});
    // 枚举要处理的长度的一半
    for (int mid = 1; mid < tot; mid <<= 1)
    {
        // 预处理好所有段都需要的W_N^k
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)}); // inv来确定采用的信号的辅角的正负，从而同时实现正逆变换
        for (int i = 1; i < mid; i ++) w[i] = w[i - 1] * w1;
        // 枚举所有长度为2 * mid的段
        for (int i = 0; i < tot; i += mid * 2)
        {   // 枚举段中的一半长度
            for (int j = 0; j < mid; j ++)
            {
                // 成对地更新元素
                auto x = a[i + j], y = w[j] * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i ++ ) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i ++ ) scanf("%lf", &b[i].x);
    // 得到不小于卷积结果长度的最小的2的幂次
    while ((1 << bit) < n + m + 1) bit ++;
    tot = 1 << bit;
    // 得到新旧下标的映射关系
    for (int i = 0; i < tot; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, -1), fft(b, -1);  // 逆变换
    for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
    fft(a, 1);  // 正变换
    for (int i = 0; i <= n + m; i ++ )
        printf("%d ", (int)(a[i].x / tot + 0.5));  // 注意结果要除以N，还有浮点数误差

    return 0;
}
