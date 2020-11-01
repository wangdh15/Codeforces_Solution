/**
 *
 * 分块：优雅的暴力方式
 * https://www.acwing.com/problem/content/244/
 *
 */


#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;
constexpr int N = 1e5 + 10, M = 350;

LL q[N];
LL s[M], add[M];
int n, m;
int len;

int get(int i) {return i / len;}


void modify(int l , int r, int d) {
    if (get(l) == get(r)) {
        for (int i = l; i <= r; i ++) q[i] += d, s[get(i)] += d;
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) q[i] += d, s[get(i)] += d, ++i;
        while (get(j) == get(r)) q[j] += d, s[get(j)] += d, --j;
        for (int k = get(i); k <= get(j); k ++) s[k] += (LL)len * d, add[k] += d;
    }
}

LL query(int l, int r) {
    
    LL res = 0;
    if (get(l) == get(r)) {
        for (int i = l; i <= r; i ++) res += q[i] + add[get(i)]; 
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) res += q[i] + add[get(i)], ++i;
        while (get(j) == get(r)) res += q[j] + add[get(j)], --j;
        for (int k = get(i); k <= get(j); k ++) res += s[k];
    }
    return res;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    len = sqrt(n);
    for (int i = 1; i <= n; i ++) {
        cin >> q[i];
        s[get(i)] += q[i];
    }
    string op;
    int l, r, d;
    while (m --) {
        cin >> op;
        if (op == "Q") {
            cin >> l >> r;
            cout << query(l, r) << '\n';
        } else {
            cin >> l >> r >> d;
            modify(l, r, d);
        }
    }
    return 0;
}

