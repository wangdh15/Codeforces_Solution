//
// Created by wangdh on 2020/10/21.
//

/**
 * 背包问题求最优的方案数。
 * 注意数组的初始化方式，method要初始化为1
 * https://www.acwing.com/problem/content/description/11/
 *
 */

#include <iostream>
using namespace std;

namespace methods_package_1 {
    constexpr int V = 1010;
    constexpr int MOD = 1e9 + 7;
    int dp[V], method[V];

    int main() {

        int n, v;
        cin >> n >> v;
        for (int i = 0; i <= v; i ++) method[i] = 1;
        while (n --) {
            int vi, wi;
            cin >> vi >> wi;
            for (int i = v; i >= vi; i --) {
                if (dp[i] == dp[i - vi] + wi) {
                    method[i] += method[i - vi];
                    method[i] %= MOD;
                }
                else if (dp[i] < dp[i - vi] + wi) {
                    dp[i] = dp[i - vi] + wi;
                    method[i] = method[i - vi];
                }
            }
        }
        cout << method[v];
        return 0;

    }
}
