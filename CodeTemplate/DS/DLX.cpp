/**
 *
 * dancing link 模板题
 * https://www.acwing.com/problem/content/description/1069/
 * 使用十字链表优化精确覆盖问题的爆搜解法
 *
 */

#include <iostream>
using namespace std;

const int N = 505, M = 5505;

int l[M], r[M], u[M], d[M], col[M], row[M], idx; // 存储每个节点的信息
int sz[N];   // 存储每一列的元素的个数
int ans[N], top; // 存储最终的答案

int n, m;

// 对十字链表进行初始化
void init() {

    for (int i = 0; i <= m; i ++) {
        l[i] = i - 1;
        r[i] = i + 1;
        u[i] = d[i] = i;
    }
    l[0] = m;
    r[m] = 0;
    idx = m + 1;
}

// 在hh 和tt这两个节点之间插入坐标为(x, y)的节点
void insert(int &hh, int &tt, int x, int y) {
    col[idx] = y, row[idx] = x;
    sz[y] ++;
    l[idx] = hh, r[idx] = tt, u[idx] = y, d[idx] = d[y];
    l[r[idx]] = idx, r[l[idx]] = idx, u[d[idx]] = idx, d[u[idx]] = idx;
    tt = idx ++;
}

// 将列p删除
void remove(int p) {

    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i]) {
        for (int j = r[i]; j != i; j = r[j]) {
            u[d[j]] = u[j];
            d[u[j]] = d[j];
            sz[col[j]] --;
        }
    }

}

// 将p列恢复
void resume(int p) {

    for (int i = u[p]; i != p; i = u[i]) {
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j;
            d[u[j]] = j;
            sz[col[j]] ++;
        }
    }
    r[l[p]] = p, l[r[p]] = p;
}

// 搜索框架
bool dfs() {

    if (!r[0]) return true;

    // 找到1元素个数最少的列
    int p = r[0];
    for (int i = r[0]; i; i = r[i]) {
        if (sz[i] < sz[p]) {
            p = i;
        }
    }
    
    // 将这一列删除
    remove(p);
    for (int i = d[p]; i != p; i = d[i]) {
        ans[++ top] = row[i];  // 枚举每一行
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]); // 将这一行中的1所在的所有列都删除
        if (dfs()) return true;

        // 恢复现场
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top --;
    }
    resume(p);
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
    if (!dfs()) cout << "No Solution!";
    else {
        for (int i = 1; i <= top; i ++) cout << ans[i] << ' ';
    }
    return 0;
}
