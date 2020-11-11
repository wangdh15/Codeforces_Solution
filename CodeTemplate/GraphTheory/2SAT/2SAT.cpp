/**
 *
 * 2SAT 模板
 * https://www.luogu.com.cn/problem/P4782
 *
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 2e6 + 5, M = 2e6 + 5;

int h[N], e[M], ne[M], idx;
int scc_cnt;
int ids[N];
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];

int n, m;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


void tarjan(int u) {
    
    dfn[u] = low[u] = ++ timestamp;
    in_stk[u] = true;
    stk[++ top] = u;
    
    for (int i = h[u]; ~i; i = ne[i]) {
        
        int node = e[i];
        if (!dfn[node]) {
            tarjan(node);
            low[u] = min(low[u], low[node]);
        } else if (in_stk[node]) low[u] = min(low[u], dfn[node]);
    }
    
    if (dfn[u] == low[u]) {
        
        ++ scc_cnt;
        int y;
        do {
            y = stk[top --];
            in_stk[y] = false;
            ids[y] = scc_cnt;
        }while (y != u);
        
    }
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(h, -1, sizeof h);
    
    cin >> n >> m;
    
    int i, a, j, b;
    while (m --) {
        cin >> i >> a >> j >> b;
        i --, j --;
        add(2 * i + !a, 2 * j + b);
        add(2 * j + !b, 2 * i + a);
    }
    
    
    for (int i = 1; i < 2 * n; i ++) {
        if (!dfn[i]) tarjan(i);
    }
    
    bool suc = true;
    for (int i = 0; i < n; i ++) {
        if (ids[2 * i] == ids[2 * i + 1]) {
            suc = false;
            break;
        }
    }
    
    if (!suc) cout << "IMPOSSIBLE";
    else {
        cout << "POSSIBLE" << '\n';
        for (int i = 0; i < n; i ++) {
            if (ids[2 * i] > ids[2 * i + 1]) cout << 1 << ' ';
            else cout << 0 << ' ';
        }
    }
    return 0;
    
    
}
