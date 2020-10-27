/**
 * 最大流dinic模板
 *
 * https://www.acwing.com/problem/content/description/2174/
 *
 */

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

constexpr int N = 1e4 + 5, M = 2e5 + 5, INF = 2e9;

int h[N], e[M], ne[M], f[M], idx;
int cur[N], d[N]; // cur 用于弧优化，d用于图分层

int n, m, S, T;


// 网络流题目将双向边加到相邻的下标，用数组模拟链表，同时存储的是反向的链表
void add(int a, int b, int c) {
    
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
    
}

// dfs， 求最大流量
int dfs(int u, int limit) {
    
    if (u == T) return limit;
    
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i;
        int node = e[i];
        if (d[node] == d[u] + 1 && f[i]) {
            int t = dfs(node, min(limit - flow, f[i]));
            if (!t) d[node] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}


// bfs，将如分层，同时初始化每个节点的cur数组，
bool bfs() {
    
    memset(d, -1, sizeof d);
    cur[S] = h[S];
    d[S] = 0;
    queue<int> qe;
    qe.push(S);
    while (qe.size()) {
        
        int ele = qe.front();
        qe.pop();
        
        for (int i = h[ele]; ~i; i = ne[i]) {
            
            int node = e[i];
            if (d[node] == -1 && f[i]) {
                d[node] = d[ele] + 1;
                cur[node] = h[node];
                if (node == T) return true;
                qe.push(node);
            }
            
        }
        
    }
    return false;
}

int dinic() {
    
    int res = 0, flow;
    while (bfs()) while (flow = dfs(S, INF)) res += flow;
    return res;
    
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(h, -1, sizeof h);
    cin >> n >> m >> S >> T;
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    
    cout << dinic();
    return 0;
    
}
