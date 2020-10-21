//
// Created by wangdh on 2020/10/21.
//

/*
 * 分组背包问题
 * 每一组的物品只能选一个
 * https://www.acwing.com/problem/content/description/9/
 */

#include <iostream>
using namespace std;

namespace group_package {

    constexpr int V = 110;
    constexpr int N = 110;

    int dp[N][V];

    int main() {

        int n, v;
        cin >> n >> v;
        for(int i = 1; i <= n; i ++) {
            int si;
            cin >> si;
            for (int j = 0; j <= v; j ++) dp[i][j] = dp[i-1][j];
            while (si --) {
                int vi, wi;
                cin >> vi >> wi;
                for (int j = v; j >= vi; j --) dp[i][j] = max(dp[i][j], dp[i-1][j-vi] + wi);
            }
        }
        cout << dp[n][v];
        return 0;

    }
}