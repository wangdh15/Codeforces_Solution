/**
 * 后缀自动机模板
 * https://www.luogu.com.cn/problem/P3804
 */

#include <iostream>
#include <cstring>

using namespace std;
typedef long long LL;
const int N = 1e6 + 5;

struct Node {
    int len, fa;
    int ch[26];
}tr[N << 1]; // 后缀自动机中的节点

int f[N << 1];  // 记录每个状态代表的所有字符串出现的次数

int last = 1, idx = 1;

int h[N << 1], e[N << 1], ne[N << 1], g_idx;  // 存储后缀链接代表的反向边
LL ans;


// 增量法构造后缀自动机
void extend(int c) {
    
    int p = last, np = last = ++idx;
    tr[np].len = tr[p].len + 1;
    // 如果一个状态包含了原始串的前缀，则其出现次数要加1
    // 。因为如果不是前缀，则必然可以从其他状态转移过来
    f[np] = 1;
    while (p && !tr[p].ch[c]) tr[p].ch[c] = np, p = tr[p].fa;
    if (!p) tr[np].fa = 1;
    else {
        int q = tr[p].ch[c];
        if (tr[q].len == tr[p].len + 1) tr[np].fa = q;
        else {
            int nq = ++idx;
            tr[nq] = tr[q];
            tr[nq].len = tr[p].len + 1;
            tr[q].fa = tr[np].fa = nq;
            while (p && tr[p].ch[c] == q) tr[p].ch[c] = nq, p = tr[p].fa;
        }
    }
}


void add(int a, int b) {
    e[g_idx] = b, ne[g_idx] = h[a], h[a] = g_idx ++;
}

// DFS，其每个状态的endpos集合的大小
void dfs(int cur) {
    
    for (int i = h[cur]; ~i; i = ne[i]) {
        dfs(e[i]);
        f[cur] += f[e[i]];
    }
    if (f[cur] > 1) ans = max(ans, (LL)f[cur] * tr[cur].len);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    
    cin >> s;
    for (auto x : s) {
        extend(x - 'a');
    }
    memset(h, -1, sizeof h);
    for (int i = 2; i <= idx; i ++) add(tr[i].fa, i);  // 在后缀链接上建立反向图，便于递归
    
    
    dfs(1);  // 递归统计所有答案中的最大值
    cout << ans;
    return 0; 
}
