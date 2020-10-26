/**
 * K-D Tree的实现，V1不支持插入和重构，V2支持插入和重构
 *  https://www.luogu.com.cn/problem/P6247
 *  
 *
 *
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

constexpr int N = 1e5 + 10;
constexpr double INF = 4e18;

struct Node {
    double x, y;
}tr[N];

double _min = INF, _max = -INF;

typedef  struct Node node;

int L[N], R[N], U[N], D[N];
int lc[N], rc[N];
int n;


auto cmp1 = [](const node &a, const node &b) -> bool {return a.x < b.x;};
auto cmp2 = [](const node &a, const node &b) -> bool {return a.y < b.y;};

inline
double sqr(double x) {return x * x;}

inline
double get_dis(int a, int b) {
    return sqr(tr[a].x - tr[b].x) + sqr(tr[a].y - tr[b].y);
}

void pushup(int mid) {
    L[mid] = R[mid] = tr[mid].x;
    U[mid] = D[mid] = tr[mid].y;
    if (lc[mid]) {
        L[mid] = min(L[mid], L[lc[mid]]);
        R[mid] = max(R[mid], R[lc[mid]]);
        U[mid] = max(U[mid], U[lc[mid]]);
        D[mid] = min(D[mid], D[lc[mid]]);
    }

    if (rc[mid]) {
        L[mid] = min(L[mid], L[rc[mid]]);
        R[mid] = max(R[mid], R[rc[mid]]);
        U[mid] = max(U[mid], U[rc[mid]]);
        D[mid] = min(D[mid], D[rc[mid]]);
    }
}


double get_max_dis(int a, int b) {

    double ans = 0;
    if (tr[a].x * 2 < L[b] + R[b]) ans += sqr(tr[a].x - R[b]);
    else ans += sqr(tr[a].x - L[b]);
    if (tr[a].y * 2 < U[b] + D[b]) ans += sqr(tr[a].y - U[b]);
    else ans += sqr(tr[a].y - D[b]);
    return ans;

}

double get_min_dis(int a, int b) {

    double ans = 0;
    if (tr[a].x < L[b]) ans += sqr(tr[a].x - L[b]);
    if (tr[a].x > R[b]) ans += sqr(tr[a].x - R[b]);
    if (tr[a].y < D[b]) ans += sqr(tr[a].y - D[b]);
    if (tr[a].y > U[b]) ans += sqr(tr[a].y - U[b]);
    return ans;

}

int build(int l, int r) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    for (int i = l;  i <= r; i ++) avx += tr[i].x, avy += tr[i].y;
    avx /= (double)(r - l + 1), avy /= (double)(r - l + 1);
    for (int i = l; i <= r; i ++) vax += sqr(tr[i].x - avx), vay += sqr(tr[i].y - avy);
    if (avx > avy) nth_element(tr + l, tr + mid, tr + r + 1, cmp1);
    else nth_element(tr + l, tr + mid, tr + r + 1, cmp2);
    lc[mid] = build(l, mid - 1);
    rc[mid] = build(mid + 1, r);
    pushup(mid);
    return mid;
}


void query_max(int l, int r, int x) {
    if (l > r) return;
    int mid = l + r >> 1;
    if (mid != x) _max = max(_max, get_dis(mid, x));
    if (l == r) return;
    double ldis = get_max_dis(x, lc[mid]), rdis = get_max_dis(x, rc[mid]);
    if (ldis > _max && rdis > _max) {
        if (ldis > rdis) {
            query_max(l, mid - 1, x);
            if (rdis > _max) query_max(mid + 1, r, x);
        } else {
            query_max(mid + 1, r, x);
            if (ldis > _max) query_max(l, mid - 1, x);
        }
    } else {
        if (ldis > _max) query_max(l, mid - 1, x);
        if (rdis > _max) query_max(mid + 1, r, x);
    }
}


void query_min(int l, int r, int x) {
    if (l > r) return ;
    int mid = l + r >> 1;
    if(mid != x) _min = min(_min, get_dis(mid, x));
    if (l == r) return ;
    double ldis = get_min_dis(x, lc[mid]), rdis = get_min_dis(x, rc[mid]);
    if (ldis < _min && rdis < _min) {
        if (ldis < rdis) {
            query_min(l, mid - 1, x);
            if (rdis < _min) query_min(mid + 1, r, x);
        } else {
            query_min(mid + 1, r, x);
            if (ldis < _min) query_min(l, mid - 1, x);
        }
    } else {
        if (ldis < _min) query_min(l, mid - 1, x);
        if (rdis < _min) query_min(mid + 1, r, x);
    }
}



int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) scanf("%lf %lf", &tr[i].x, &tr[i].y);
    build(1, n);

    for (int i = 1; i <= n; i ++) query_min(1, n, i), query_max(1, n, i);
    printf("%.4lf %.4lf", sqrt(_min), sqrt(_max));
    return 0;

}


