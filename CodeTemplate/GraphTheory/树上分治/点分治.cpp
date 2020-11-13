/**
 *
 * https://www.luogu.com.cn/problem/P3806
 * 点分治模板题
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

const int N = 2e4 + 5, M = 2 * N, MAX_K = 1e7, MAX_QUERY_NUM = 105;

int h[N], e[M], ne[M], w[M], idx;
int query[MAX_QUERY_NUM];
bool ans[MAX_QUERY_NUM];
int sz[N], max_child[N];
int root, cur_tree_size;
bool vis[N], judge[MAX_K];
int rec[N], top;
int rec2[N], top2;
int dis[N];


int n, m;


void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

void get_root(int u, int fa) {
    
    sz[u] = 1, max_child[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa || vis[node]) continue;
        get_root(node, u);
        sz[u] += sz[node];
        max_child[u] = max(max_child[u], sz[node]);
    }
    max_child[u] = max(max_child[u], cur_tree_size - sz[u]);
    if (max_child[u] < max_child[root]) root = u;
}


void get_dis(int u, int fa) {
    
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa || vis[node]) continue;
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
        dis[node] = w[i];
        rec2[top2 ++] = dis[node];
        get_dis(node, root);
        
        for (int j = 0; j < top2; j ++) {
            for (int k = 1; k <= m; k ++) {
                int t = query[k] - rec2[j];
                if (t >= 0) ans[k] |= judge[t];
            }
        }
        
        for (int j = 0; j < top2; j ++) {
            if (rec2[j] <= 1e7 && !judge[rec2[j]]) rec[top ++] = rec2[j], judge[rec2[j]] = true; 
        }
        top2 = 0;
    }
    
    for (int i = 0; i < top; i ++) judge[rec[i]] = false;
    top = top2 = 0;
    
}

void get_size(int u, int fa) {
    sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (node == fa || vis[node]) continue;
        get_size(node, u);
        sz[u] += sz[node];
    }
}

void solve(int u) {
    
    root = 0;
    max_child[0] = 2e9;
    
    get_root(u, 0);
    
    calc();
    
    // cout << root << endl;
    // for (int i = 1; i <= m; i ++) cout << ans[i] << ' ';
    // cout << endl;
    
    vis[root] = true;
    
    get_size(root, 0);


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
    cin >> n >> m;
    for (int i = 1; i < n; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    
    for (int i = 1; i <= m; i ++) cin >> query[i];
    
    judge[0] = true;
    cur_tree_size = n;
    solve(1);
    
    for (int i = 1; i <= m; i ++) {
        if (ans[i]) cout << "AYE" << '\n';
        else cout << "NAY" << '\n';
    }
    return 0;   
}
