//
// Created by wangdh on 2020/10/21.
//

/*
 * 有依赖的背包问题
 * https://www.acwing.com/problem/content/description/10/
 *
 * 状态dp[i][j] 表示在以i为根的子树中选，且体积为j的最大价值
 * 转移的时候，将每个子树看做一系列体积的分组背包问题。每个子树是一个组，一个组中只能选择一个物品
 *
 */


#include <iostream>
#include <vector>
using namespace std;


namespace tree_package {
    constexpr int N = 110;
    constexpr int V = 110;

    int dp[N][V];
    int v[N], w[N];

    vector<int> g[N];
    int n, v_all;
    int root;

    void dfs(int u) {

        for (auto x : g[u]) dfs(x);
        for (auto x : g[u]) {
            for (int j = v_all; j >= 0; j --) {
                for (int i = j; i >= 0; i --) {
                    dp[u][j] = max(dp[u][j], dp[u][j - i] + dp[x][i]);
                }
            }
        }
        for (int i = v_all; i >= v[u]; i --) dp[u][i] = w[u] + dp[u][i - v[u]];
        for (int i = v[u] - 1; i >= 0; i --) dp[u][i] = 0;
        return;
    }

    int main() {

        cin >> n >> v_all;

        for (int i = 1; i <= n; i ++) {
            int vi, wi, pi;
            cin >> vi >> wi >> pi;
            v[i] = vi;
            w[i] = wi;
            if (pi == -1) root = i;
            else g[pi].push_back(i);
        }

        dfs(root);
        cout << dp[root][v_all];
        return 0;

    }
}

