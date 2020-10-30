/**
 * 线段树套平衡树，其中平衡树直接套STL
 * https://www.acwing.com/problem/content/description/2490/
 *
 */

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

constexpr int N = 5e4 + 5, INF = 2e9;
struct Node {
    int l, r;
    multiset<int> s;
};

typedef struct Node node;
node tr[N * 4];
int n, m;
int q[N];

void build(int u, int l, int r) {

    tr[u].l = l;
    tr[u].r = r;
    tr[u].s.insert(-INF);
    tr[u].s.insert(INF);
    for (int i = l; i <= r; i ++) tr[u].s.insert(q[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}


void change(int u, int pos, int x) {
    
    tr[u].s.erase(tr[u].s.find(q[pos]));
    tr[u].s.insert(x);
    if (tr[u].l == tr[u].r) return;
    int mid = tr[u].l  + tr[u].r >> 1;
    if (pos <= mid) change(u << 1, pos, x);
    else change(u << 1 | 1, pos, x);
}

int query(int u, int l, int r, int x) {

    if (tr[u].l >= l && tr[u].r <= r) {
        auto it = tr[u].s.lower_bound(x);
        --it;
        return *it;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int res = -INF;
    if (l <= mid) res = max(res, query(u << 1, l, r, x));
    if (r > mid) res = max(res, query(u << 1 | 1, l, r, x));
    return res;

}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> q[i];
    build(1, 1, n);

    int op;
    int l, r, x, pos;
    while (m --) {
        cin >> op;
        if (op == 1) {
            cin >> pos >> x;
            change(1, pos, x);
            q[pos] = x;
        } else {
            cin >> l >> r >> x;
            cout << query(1, l, r, x) << '\n';
        }
    }
    return 0;
}


