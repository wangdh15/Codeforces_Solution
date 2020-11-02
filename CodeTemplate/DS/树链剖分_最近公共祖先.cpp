/**
 *
 * https://www.luogu.com.cn/problem/P3379
 *
 * 树链剖分求最近公共祖先
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 5e5 + 5, M = N * 2;

int h[N], e[M], ne[M], idx;
int sz[N], fa[N], son[N], dep[N], top[N];
int n, m, root;

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
    top[cur] = t;
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa[cur]) continue;
        if (node == son[cur]) dfs2(node, t);
        else dfs2(node, node);
    }
}

int lca(int a, int b) {


    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        a = fa[top[a]];
    }
    return dep[a] < dep[b] ? a : b;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, -1, sizeof h);

    cin >> n >> m >> root;
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    dfs1(root, -1, 1);
    dfs2(root, root);

    while (m --) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
    return 0;

}
