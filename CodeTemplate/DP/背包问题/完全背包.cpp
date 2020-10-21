//
// Created by wangdh on 2020/10/21.
//

/**
 * 完全背包问题，每个物品可以选择无限多次
 * https://www.acwing.com/problem/content/3/
 */

#include <iostream>
using namespace std;

namespace complete_package {
    constexpr int V = 1010;

    int dp[V];

    int main() {

        int n, v;
        cin >> n >> v;
        while (n --) {
            int vi, wi;
            cin >> vi >> wi;
            for (int i = vi; i <= v; i ++) dp[i] = max(dp[i], dp[i - vi] + wi);
        }
        cout << dp[v];
        return 0;
    }
}
