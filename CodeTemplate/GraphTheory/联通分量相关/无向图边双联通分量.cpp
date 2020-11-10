/**
 *
 * tarjan算法求无向图边双联通分量，同时求出了所有的桥。
 * 将同一个边双联通分量内的点缩点之后，得到的拓扑结构为一棵树
 *
 * https://www.acwing.com/problem/content/397/
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

const int N = 5005, M = 2e4 + 5;

int h[N], e[M], ne[M], idx;

int n, m;
int stk[N], top;
bool is_bridge[M]; // 记录每个边是不是桥
int dfn[N], low[N], timestamp;
int ids[N], dcc_cnt; // 记录每个点所属的联通分量的编号
int deg[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

// 传入当前判断的点和从哪个边过来的
void tarjan(int n, int from) {

    dfn[n] = low[n] = ++timestamp;
    stk[++top] = n;
    for (int i = h[n]; ~i; i = ne[i]) {
        int node = e[i];
        if (!dfn[node]) {
            tarjan(node, i);
            low[n] = min(low[n], low[node]);
            if (dfn[n] < low[node]) is_bridge[i] = is_bridge[i ^ 1] = true; // 找到桥
        } else if (i != (from ^ 1)) low[n] = min(low[n], dfn[node]); // 只可能存在反向边，所以不用instack
    }

    if (dfn[n] == low[n]) { // 说明自己一下的节点最多只能到自己，栈顶的元素构成了一个边双联通分量
        ++dcc_cnt;
        int y;
        do {
            y = stk[top--];
            ids[y] = dcc_cnt; // 每个节点分配一个编号，可以用来直接缩点建图
        }while(y != n);
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(h, -1 ,sizeof h);
    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    tarjan(1, -1);

    for (int i = 0; i < idx; i ++) {
        if (is_bridge[i]) {
            deg[ids[e[i]]] ++;  // 找到缩点之后的叶子节点
        }
    }

    int res = 0;
    for (int i = 1; i <= dcc_cnt; i ++) {
        if (deg[i] == 1) res ++;
    }

    cout << (res + 1) / 2;
    return 0;


}
