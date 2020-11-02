/**
 *https://www.acwing.com/problem/content/920/
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;
int h[N], e[N], ne[N], idx;
int n, m;
int ids[N], cnt;
int son[N], sz[N], top[N], dep[N], fa[N];

struct Node {
    int l, r;
    int s, same;
}tr[N * 4];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void dfs1(int cur, int father, int de) {
    dep[cur] = de;
    sz[cur] = 1;
    fa[cur] = father;
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        dfs1(node, cur, de + 1);
        sz[cur] += sz[node];
        if (sz[node] > sz[son[cur]]) son[cur] = node;
    }
}

void dfs2(int cur, int t) {
    ids[cur] = ++cnt;
    top[cur] = t;
    if (!son[cur]) return;
    dfs2(son[cur], t);
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == son[cur]) continue;
        dfs2(node, node);
    }
}

void pushup(int u) {

    tr[u].s = tr[u << 1].s + tr[u << 1 | 1].s;

}


void build(int u, int l, int r) {
    tr[u] = {l, r, 0, -1};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void eval(int u, int v) {
    tr[u].s = v * (tr[u].r - tr[u].l + 1);
    tr[u].same = v;
}

void pushdown(int u) {

    if (tr[u].same == -1) return;
    eval(u << 1, tr[u].same);
    eval(u << 1 | 1, tr[u].same);
    tr[u].same = -1;

}

void modify(int u, int l, int r, int v) {

    if (tr[u].l >= l && tr[u].r <= r) {
        eval(u, v);
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, v);
        if (r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].s;
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    pushdown(u);
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

int install(int x) {

    int cur_sum = 0, all_sum = 0;
    while (top[x] != top[1]) {
        cur_sum += query(1, ids[top[x]], ids[x]);
        modify(1, ids[top[x]], ids[x], 1);
        all_sum += ids[x] - ids[top[x]] + 1;
        x = fa[top[x]];
    }
    cur_sum += query(1, ids[1], ids[x]);
    all_sum += ids[x] - ids[1] + 1;
    modify(1, ids[1], ids[x], 1);
    return all_sum - cur_sum;
}


int uninstall(int x) {

    int res = query(1, ids[x], ids[x]  + sz[x] - 1);
    modify(1, ids[x], ids[x] + sz[x] - 1, 0);
    return res;

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    memset(h, -1, sizeof h);

    cin >> n;

    for (int i = 1; i <= n - 1; i ++) {
        int x;
        cin >> x;
        add(x + 1, i + 1);
    }


    dfs1(1, -1, 1);
    dfs2(1, 1);

    build(1, 1, n);


    cin >> m;
    string op;
    int x;
    while (m --) {
        cin >> op >> x;
        if (op[0] == 'i') {
            cout << install(x + 1) << '\n';

        } else {
            cout << uninstall(x + 1) << '\n';
        }
    }
    return 0;

}



