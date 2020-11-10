/**
 * 可以用来求将无向图的任何一个点删除之后，剩余的联通分量的个数
 * https://www.acwing.com/problem/content/1185/
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e4 + 5, M = 3e4 + 5;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, res, cnt;
int n, m;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u) {
    
    dfn[u] = low[u] = ++ timestamp;
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int node = e[i];
        if (!dfn[node]) {
            tarjan(node);
            low[u] = min(low[u], low[node]);
            if (low[node] >= dfn[u]) cnt ++;
        } else low[u] = min(low[u], dfn[node]);
    }
    if (u != root) cnt ++;  // cnt表示将u删除之后，u所在的联通分量变成了多少个联通分量
    res = max(res, cnt);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    
    while (true) {
        cin >> n >> m;
        if (!n && !m ) break;
        memset(h, -1, sizeof h);
        memset(dfn, 0, sizeof dfn);
        idx = 0;
        timestamp = 0;
        res = cnt = 0;
        while (m --) {
            int a, b;
            cin >> a >> b;
            add(a, b);
            add(b, a);
        }
        
        for (root = 0; root < n; root ++) {
            if (!dfn[root]) {
                cnt ++;
                tarjan(root);
            }
        }
        cout << res + cnt - 1 << '\n';
        
    }
    
}
