/**
 *https://www.acwing.com/problem/content/2570/
 * 
 * 将子树序列和两点之间的路径转为线段树维护
 *
 */

#include <iostream>
#include <cstring>
using namespace std;


typedef long long LL;

const int N = 1e5 + 10, M = 2 * N;

int h[N], e[M], ne[M], idx;
int w[N], nw[N], id[N], cnt;
int n, m;
int sz[N], fa[N], dep[N], son[N], top[N];

struct Node {
    int l, r;
    LL s, add;
}tr[4 * N];


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void dfs1(int cur, int father, int de) {
    dep[cur] = de;
    fa[cur] = father;
    sz[cur] = 1;
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == father) continue;
        dfs1(node, cur, de + 1);
        sz[cur] += sz[node];
        if (sz[node] > sz[son[cur]]) son[cur] = node;
    }
}


void dfs2(int cur, int t) {

    id[cur] = ++cnt;
    nw[cnt] = w[cur];
    top[cur] = t;
    if (!son[cur]) return;
    dfs2(son[cur], t);
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa[cur] || node == son[cur]) continue;
        dfs2(node, node);
    }
}

void pushup(int u) {
    tr[u].s = tr[u << 1].s + tr[u << 1 | 1].s;
}

void eval(int u, LL ad) {
    tr[u].s += ad * (tr[u].r - tr[u].l + 1);
    tr[u].add += ad;
}


void pushdown(int u) {

    eval(u << 1, tr[u].add);
    eval(u << 1 | 1, tr[u].add);
    tr[u].add = 0;

}

void build(int u, int l, int r) {

    tr[u].l = l;
    tr[u].r = r;
    if (l == r) {
        tr[u].s = nw[l];
        return;
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int v) {

    if (tr[u].l >= l && tr[u].r <= r) eval(u, v);
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, v);
        if (r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
}

LL query(int u, int l, int r) {

    if (tr[u].l >= l && tr[u].r <= r) return tr[u].s;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}


void update_path(int u, int v, int k) {

    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        modify(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    modify(1, id[v], id[u], k);
}


void update_tree(int u, int k) {
    modify(1, id[u], id[u] + sz[u] - 1, k);
}

LL query_tree(int u) {

    return query(1, id[u], id[u] + sz[u] - 1);

}

LL query_path(int u, int v) {

    LL  res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);
    return res;

}




int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> w[i];
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    dfs1(1, -1, 1);

    dfs2(1, 1);

    build(1, 1, n);

    cin >> m;
    int op, u, v, k;
    while (m --) {

        cin >> op >> u;
        if (op == 1) {
            cin >> v >> k;
            update_path(u, v, k);
        } else if (op == 2) {
            cin >> k;
            update_tree(u, k);
        } else if (op == 3) {
            cin >> v;
            cout << query_path(u, v) << '\n';
        } else {
            cout << query_tree(u) << '\n';
        }
    }
    return 0;
}
