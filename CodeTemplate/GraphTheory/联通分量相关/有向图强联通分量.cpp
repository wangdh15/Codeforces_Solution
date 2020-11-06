/**
 *
 * https://www.acwing.com/problem/content/description/1176/
 *
 * 使用tarjan算法求有向图强联通分量
 *
 */

#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

const int N = 1e4 + 5, M = 5e4 + 5;

int h[N], e[M], ne[M], idx;
int dfn[N], low[N];
int ids[N], scc_cnt, sz[N];
int timestamp;
bool instk[N];
int dout[N];
int n, m;

stack<int> stk;


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


// tarjan算法求有向图的强联通分量
void tarjan(int cur) {
    
    stk.push(cur);
    instk[cur] = true;  // 当前节点入栈
    dfn[cur] = low[cur] = ++ timestamp;
    for (int i = h[cur]; ~i; i = ne[i]) {  // 遍历所有孩子节点
        int node = e[i];
        
        if (!dfn[node]) {  // 没有遍历过，深度优先遍历
            tarjan(node);
            low[cur] = min(low[cur], low[node]);
        } else if (instk[node]) {  // 遍历过，且还在栈中
            low[cur] = min(low[cur], low[node]);
        }
    }
    
    // 表示当前点是其所在联通分量第一个搜到的点
    // 将栈顶元素弹出，且它们都在一个联通分量中
    if (dfn[cur] == low[cur]) {  
        scc_cnt ++;
        int y;
        do {
            y = stk.top();
            stk.pop();
            sz[scc_cnt] ++;
            instk[y] = false;
            ids[y] = scc_cnt;
        } while (y != cur);
    }
}


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    memset(h, -1, sizeof h);
    
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    // 对整个图求一次强连通分量已经拓扑序
    // 编号的逆序就是强连通分量的拓扑序
    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) tarjan(i);
    }
    
    // 统计每个强连通分量的出度
    for(int i = 1; i <= n; i ++) {
        for(int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = ids[i], b = ids[k];
            if (a != b) dout[a] ++;
        }
    }
    
    // 查看出度为零的强联通分量的个数
    int zeros = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i ++) {
        if (!dout[i]) {
            zeros ++;
            sum += sz[i];
            if (zeros > 1) {
                sum = 0;
                break;
            }
        }
    }
    cout << sum;
    return 0;
}


