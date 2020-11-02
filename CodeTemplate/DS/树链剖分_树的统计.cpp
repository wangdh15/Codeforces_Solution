/**
 * https://loj.ac/problem/10138
 *
 *
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 3e4 + 5, M = 2 * N, INF = 2e9;

int fa[N], sz[N], son[N], dep[N], top[N];
int w[N], ids[N], nw[N], cnt;
int n, m;
int h[N], e[M], ne[M], idx;

struct Node {
    int l, r;
    int ma, sum;
}tr[4 * N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int cur, int father, int de) {

    sz[cur] = 1;
    fa[cur] = father;
    dep[cur] = de;
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == father) continue;
        dfs1(node, cur, de + 1);
        sz[cur] += sz[node];
        if (sz[node] > sz[son[cur]]) son[cur] = node;
    }
}

void dfs2(int cur, int t) {
    top[cur] = t;
    ids[cur] = ++cnt;
    nw[cnt] = w[cur];
    if (!son[cur]) return;
    dfs2(son[cur], t);
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa[cur] || node == son[cur]) continue;
        dfs2(node, node);
    }
}



void pushup(int u) {

    tr[u].ma = max(tr[u << 1].ma, tr[u << 1 | 1].ma);
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;

}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, nw[l], nw[l]};
    } else {
        tr[u].l = l;
        tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int loc, int x) {

    if (tr[u].l == tr[u].r) {
        tr[u].sum = tr[u].ma = x;
        return;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (loc <= mid) modify(u << 1, loc, x);
        else modify(u << 1 | 1, loc, x);
        pushup(u);
    }

}

int query_sum(int u, int l, int r) {

    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    if (l <= mid) res += query_sum(u << 1, l, r);
    if (r > mid) res += query_sum(u << 1 | 1, l, r);
    return res;
}

int query_max(int u, int l, int r) {

    if (tr[u].l >= l && tr[u].r <= r) return tr[u].ma;
    int res = -INF;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) res = max(res, query_max(u << 1, l, r));
    if (r > mid) res = max(res, query_max(u << 1 | 1, l, r));
    return res;

}

int query_path_max(int u, int v) {
    int res = -INF;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = max(res, query_max(1, ids[top[u]], ids[u]));
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res = max(res, query_max(1, ids[v], ids[u]));
    return res;
}

int query_path_sum(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query_sum(1, ids[top[u]], ids[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query_sum(1, ids[v], ids[u]);
    return res;
}

void modify_node(int u, int v) {
    modify(1, ids[u], v);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, -1, sizeof h);

    cin >> n;
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    for (int i = 1; i <= n; i ++) cin >> w[i];

    dfs1(1, -1, 1);


    dfs2(1, 1);

//    exit(0);

    build(1, 1, n);

    cin >> m;

    string op;
    int u, v, t;
    while (m -- ) {

        cin >> op;
        if (op == "CHANGE") {
            cin >> u >> t;
            modify_node(u, t);
        } else if (op == "QMAX") {
            cin >> u >> v;
            cout << query_path_max(u, v) << '\n';
        } else {
            cin >> u >> v;
            cout << query_path_sum(u, v) << '\n';
        }
    }
    return 0;

}
