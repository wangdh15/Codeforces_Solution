/**
 * https://www.acwing.com/problem/content/1177/
 *
 */

#include <iostream>
#include <cstring>
#include <unordered_set>
using namespace std;

const int N = 1e5 + 10, M = 2e6 + 10;

int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N];
int ids[N], scc_cnt, scc_size[N];
bool in_stk[N];
int stk[N], tt;
int timestamp;
int dout[N], din[N];
int dp1[N], dp2[N];

int n, m, x;

void add(int h[], int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

// 标准的tarjan算法
void tarjan(int cur) {
    in_stk[cur] = true;
    stk[++tt] = cur;
    dfn[cur] = low[cur] = ++timestamp;
    for (int i = h[cur]; ~i; i = ne[i]) {
        int node = e[i];
        if (!dfn[node]) {
            tarjan(node);
            low[cur] = min(low[cur], low[node]);
        } else if (in_stk[node]) low[cur] = min(low[cur], dfn[node]);
    }
    if (dfn[cur] == low[cur]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[tt --];
            in_stk[y] = false;
            scc_size[scc_cnt] ++;
            ids[y] = scc_cnt;
        } while (y != cur);
    }

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    cin >> n >> m >> x;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(h, a, b);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) tarjan(i);
    }
    // 建立缩点之后的图
    unordered_set<long long> se;
    for (int i = 1; i <= n; i ++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int node = e[j];
            int idx = ids[i], idy = ids[node];
            if (idx == idy) continue;
            if (se.count(idx * 100000ll + idy)) continue;
            se.insert(idx * 100000ll + idy);
            add(hs, idx, idy);
            din[idy] ++;
            dout[idx] ++;
        }
    }


    // DAG上DP，直接按照拓扑序即可
    for (int i = scc_cnt; i >= 1; i --) {
        if (!dp1[i]) {
            dp1[i] = scc_size[i];
            dp2[i] = 1;
        }
        for (int j = hs[i]; ~j; j = ne[j]) {
            int node = e[j];
            if (dp1[i] + scc_size[node] > dp1[node]) {
                dp1[node] = dp1[i] + scc_size[node];
                dp2[node] = dp2[i];
            } else if (dp1[i] + scc_size[node] == dp1[node]) {
                dp2[node] += dp2[i];
                dp2[node] %= x;
            }
        }
    }

    int res1 = -1, res2 = 0;
    for (int i = 1; i <= scc_cnt; i ++) {
        if (dp1[i] > res1) {
            res1 = dp1[i];
            res2 = dp2[i];
        } else if (dp1[i] == res1){
            res2 += dp2[i];
            res2 %= x;
        }
    }
    cout << res1 << '\n' << res2;
    return 0;
}

