/**
 *
 * https://www.luogu.com.cn/problem/P4178
 * 点分治+线段树/树状数组/平衡树
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 4e4 + 5, M = 2 * N, K = 2e4 + 5;
int h[N], e[M], ne[M], w[M], idx;

int root, sz[N], max_child[N], cur_tree_size;
int rec[N], top;
int rec2[N], top2;
bool vis[N];
int dis[N];
int n, k;
LL ans;


struct Node{
    int l, r, s;
}tr[4 * K];


void pushup(int u) {
    tr[u].s = tr[u << 1].s + tr[u << 1 | 1].s;
}


void build(int u, int l, int r) {
    tr[u] = {l, r, 0};
    if (l == r) {
        if (l == 0) tr[u].s = 1;
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r) {
        tr[u].s += v;
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) modify(u << 1, x, v);
    else modify(u << 1 | 1, x, v);
    pushup(u);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].s;
    int res = 0;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}


void add(int a, int b, int c) {

    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;

}


void get_root(int u, int fa) {

    sz[u] = 1, max_child[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (vis[node] || node == fa) continue;
        get_root(node, u);
        sz[u] += sz[node];
        max_child[u] = max(max_child[u], sz[node]);
    }
    max_child[u] = max(max_child[u], cur_tree_size - sz[u]);
    if (max_child[u] < max_child[root]) root = u;
}


void get_size(int u, int fa) {

    sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (vis[node] || node == fa) continue;
        get_size(node, u);
        sz[u] += sz[node];
    }

}

void get_dis(int u, int fa) {

    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (vis[node] || node == fa) continue;
        dis[node] = dis[u] + w[i];
        rec2[top2 ++] = dis[node];
        get_dis(node, u);
    }
}



void calc() {

    dis[root] = 0;
    for (int i = h[root]; ~i; i = ne[i]) {
        int node = e[i];
        if (vis[node]) continue;
        dis[node] = dis[root] + w[i];
        rec2[top2 ++] = dis[node];
        get_dis(node, root);

        for (int j = 0; j < top2; j ++) {
            int t = rec2[j];
            if (t > k) continue;
            ans += query(1, 0, k - t);
        }

        for (int j = 0; j < top2; j ++) {
            if (rec2[j] <= k) rec[top ++] = rec2[j], modify(1, rec2[j], 1);
        }

        top2 = 0;

    }

    for (int i = 0; i < top; i ++) modify(1, rec[i], -1);
    top = 0;

}


void solve(int u) {

    root = 0;
    get_root(u, 0);

    calc();

    get_size(root, 0);
    vis[root] = true;

    for (int i = h[root]; ~i; i = ne[i]) {
        int node = e[i];
        if (vis[node]) continue;
        cur_tree_size = sz[node];
        solve(node);
    }
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, -1, sizeof h);

    cin >> n;
    for (int i = 1; i < n; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    cin >> k;
    cur_tree_size = n;
    max_child[0] = 2e9;
    build(1, 0, k);
    solve(1);

    cout << ans;
    return 0;

}
