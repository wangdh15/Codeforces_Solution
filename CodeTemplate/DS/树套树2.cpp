/**
 *
 * 线段树套平衡树
 * 本题实现的是线段树套Splay
 * https://www.luogu.com.cn/problem/P3380
 *
 */


#include <iostream>
using namespace std;

constexpr int N = 5e4, M = 4 * N * 2 + N * 17 ,INF = 2147483647;

struct Node {
    int s[2];
    int p, v;
    int size;
    void init(int _v, int _p) {
        v = _v;
        p = _p;
        size = 1;
    }
};

typedef struct Node node;

node tr[M];
int L[N * 4], R[N * 4], T[N * 4], idx;
int n, m;
int q[N];


void pushup(int u) {
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[y].s[k]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y);
    pushup(x);
}

void splay(int &root, int x, int k) {
    
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int &root, int v) {
    
    int u = root, p = 0;
    while (u) {
        p = u, u = tr[u].s[v > tr[u].v];
    } 
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(root, u, 0);
}

void update(int &root, int x, int y) {
    
    
    int u = root;
    while (u) {
        if (tr[u].v == x) break;
        u = tr[u].s[x > tr[u].v];
    }
    
    splay(root, u, 0);
    int l = tr[u].s[0], r = tr[u].s[1];
    while (tr[l].s[1]) l = tr[l].s[1];
    while (tr[r].s[0]) r = tr[r].s[0];
    
    splay(root, l, 0), splay(root, r, l);
    tr[r].s[0] = 0;
    pushup(r);
    pushup(l);
    insert(root, y);
    
}

int get_prev(int root, int v) {
    
    int u = root, res;
    while (u) {
        if (tr[u].v >= v) u = tr[u].s[0];
        else res = tr[u].v, u = tr[u].s[1];
    }
    return res;
}

int get_next(int root, int v) {
    int u = root, res;
    while (u) {
        if (tr[u].v <= v) u = tr[u].s[1];
        else res = tr[u].v, u = tr[u].s[0];
    }
    return res;
}

int get_rank_by_key(int root, int v) {
    
    int u = root, res = 0;
    while (u) {
        if (tr[u].v >= v) u = tr[u].s[0];
        else res += tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return res;
}


void build(int u, int l, int r) {
    
    L[u] = l;
    R[u] = r;
    insert(T[u], -INF);
    insert(T[u], INF);
    for (int i = l; i <= r; i ++) insert(T[u], q[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void change(int u, int pos, int x) {
    
    update(T[u], q[pos], x);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (pos <= mid) change(u << 1, pos, x);
    else change(u << 1 | 1, pos, x);

}

int query_rank_by_key(int u, int l, int r, int v) {
    
    if (L[u] >= l && R[u] <= r) return get_rank_by_key(T[u], v);
    int res = 0;
    int mid = L[u] + R[u] >> 1;
    if (l <= mid) res += query_rank_by_key(u << 1, l, r, v) - 1;
    if (r > mid) res += query_rank_by_key(u << 1 | 1, l, r, v) - 1;
    return res + 1;
}

int query_key_by_rank(int u, int l, int r, int k) {
    
    int ll = -1, rr = 1e8 + 3;
    while (ll < rr) {
        int mid = ll + rr + 1 >> 1;
        if (query_rank_by_key(u, l, r, mid) <= k) ll = mid;
        else rr = mid - 1;
    }
    return ll;
}


int query_prev(int u, int l, int r, int x) {
    
    if (L[u] >= l && R[u] <= r) return get_prev(T[u], x);
    int res = -INF;
    int mid = L[u] + R[u] >> 1;
    if (l <= mid) res = max(res, query_prev(u << 1, l, r, x));
    if (r > mid) res = max(res, query_prev(u << 1 | 1, l, r, x));
    return res;
}

int query_next(int u, int l, int r, int x) {
    
    if (L[u] >= l && R[u] <= r) return get_next(T[u], x);
    int res = INF;
    int mid = L[u] + R[u] >> 1;
    if (l <= mid) res = min(res, query_next(u << 1, l, r, x));
    if (r > mid) res = min(res, query_next(u << 1 | 1, l, r, x));
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
    int pos, l, r, k, x;
    while (m --) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            cout << query_rank_by_key(1, l, r, x) << '\n';
        } else if (op == 2) {
            cin >> l >> r >> k;
            cout << query_key_by_rank(1, l, r, k) << '\n';
        } else if (op == 3) {
            cin >> pos >> x;
            change(1, pos, x);
            q[pos] = x;
        } else if (op == 4) {
            cin >> l >> r >> x;
            cout << query_prev(1, l, r, x) << '\n';
        } else {
            cin >> l >> r >> x;
            cout << query_next(1, l, r, x) << '\n';
        }
    }
    return 0;
}
