/**
 * tarjan算法求无向图点双联通分量
 *
 * 能够同时求出所有的割点，并将同一个点双联通分量内部的点存储到数组中
 * 每一个割点至少属于两个点双联通分量
 * 需要注意一个单点的情况的特判
 *  
 *  https://www.luogu.com.cn/problem/P3225
 *
 */

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long LL;

const int N = 505, M = 2005;

int h[N], e[M], ne[M], idx;
int stk[N], top;  
vector<int> dcc[N]; // 存储每个联通分量中的节点
int dcc_cnt; // 记录当前找到的联通分量的个数
bool cut[N];  // 标记每个点是不是割点
int dfn[N], low[N], timestamp;
int root;  // 全局变量，用于root特判

int n, m;

void add(int a,  int b) {

    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;

}

// 求点双联通分量的板子
// 由于每个割点至少属于两个联通分量，所以不能够直接赋给每个点一个其所属的编号
// 这里用一个vector数组存储每个联通分量内部的所有点
void tarjan(int u) {

    stk[++top] = u;
    dfn[u] = low[u] = ++timestamp;

    if (u == root && h[u] == -1) { // 孤立的一个点的特判
        dcc_cnt ++;
        dcc[dcc_cnt].push_back(u);
        return;
    }

    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) { 
        int node = e[i];
        if (!dfn[node]) {
            tarjan(node);
            low[u] = min(low[u], low[node]);
            if (low[node] >= dfn[u]) {  // 说明node及其下面的节点在i这条边删除之后会形成一个孤立的联通分量
                cnt ++;
                if (u != root || cnt > 1) cut[u] = true; // 判断当前节点是否是割点
                ++ dcc_cnt;
                int y;
                do {  // 将栈中的元素都弹出来，形成一个联通分量
                    y = stk[top --];
                    dcc[dcc_cnt].push_back(y);
                } while (y != node);
                dcc[dcc_cnt].push_back(u); // 将当前点也加入到其中
            }
        } else low[u] = min(low[u], dfn[node]);  // 前向边，更新low
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;
    while (cin >> m, m) {
        for (int i = 1; i <= dcc_cnt; i ++) dcc[i].clear();
        memset(h, -1, sizeof h);
        memset(cut, false, sizeof cut);
        memset(dfn, 0, sizeof dfn);
        n = idx = timestamp = top = dcc_cnt = 0;
        while (m --) {
            int a, b;
            cin >> a >> b;
            add(a, b);
            add(b, a);
            n = max(a, n);
            n = max(b, n);
        }
        for (root = 1; root <= n; root ++) {
            if(!dfn[root]) tarjan(root);
        }
        int res = 0;
        LL num = 1;
        for (int i = 1; i <= dcc_cnt; i ++) {
            int cnt = 0;
            for (int j = 0; j < dcc[i].size(); j ++) {
                if (cut[dcc[i][j]]) cnt ++;
            }
            if (cnt == 0) {
                if (dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                else res ++;
            } else if (cnt == 1) {
                res ++, num *= dcc[i].size() - 1;
            }
        }
        cout << "Case " << T ++ << ": " << res << ' ' << num << '\n';
    }
    return 0;
}
