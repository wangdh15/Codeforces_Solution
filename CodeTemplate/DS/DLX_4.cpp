/**
 * DLX解决重复覆盖问题，搜索框架为IDA*
 * 注意，删除的操作和精确覆盖问题的操作是不同的。
 *
 * https://www.acwing.com/problem/content/description/2715/
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 110, M = 1e4 + 10;

int l[M], r[M], u[M], d[M], col[M], row[M], idx;
int s[N];
int ans[N];
int n, m;
bool st[N];

void init() {
    
    for (int i = 0; i <= m; i ++) {
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}


void insert(int &hh, int &tt, int x, int y) {
    col[idx] = y, row[idx] = x;
    s[y] ++;
    l[idx] = tt, r[idx] = hh, u[idx] = y, d[idx] = d[y];
    l[r[idx]] = idx, r[l[idx]] = idx, u[d[idx]] = idx, d[u[idx]] = idx;
    tt = idx ++;
}


// 估价函数，将某一列为1的行都选上，但是只计算一次
int h() {
    memset(st, false, sizeof st);
    int res = 0;
    for (int i = r[0]; i; i = r[i]) {
        if (st[i]) continue;
        st[i] = true;
        res ++;
        for (int j = d[i]; j != i; j = d[j]) {
            for (int k = r[j]; k != j; k = r[k]) st[col[k]] = true;
        }
    }
    return res;
}



// 删除p所在的列，将每个元素和其左右邻居断开，但是p这个点不会断开
void remove(int p) {
    for (int i = d[p]; i != p; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}

// 恢复p所在的列
void resume(int p) {
    for (int i = u[p]; i != p; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}

// IDA*框架
bool dfs(int k, int max_dep) {
    
    if (k + h() > max_dep) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i]) {
        if (s[i] < s[p]) {
            p = i;
        }
    }
    
    for (int i = d[p]; i != p; i = d[i]) {
        ans[k] = row[i];
        remove(i);
        for (int j = r[i]; j != i; j = r[j]) remove(j);
        if (dfs(k + 1, max_dep)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(j);
        resume(i);
    }
    return false;
    
}


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    init();
    
    for (int i = 1; i <= n; i ++) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= m; j ++) {
            int x;
            cin >> x;
            if (x) insert(hh, tt, i, j);
        }
    }
    int dep = 1;
    while (!dfs(0, dep)) dep ++;
    cout << dep << '\n';
    for (int i = 0; i < dep; i ++) cout << ans[i] << ' ';
    return 0;
}
