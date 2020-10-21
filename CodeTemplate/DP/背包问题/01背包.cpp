//
// Created by wangdh on 2020/10/21.
//

/**
 * 01背包问题s
 * https://www.acwing.com/problem/content/2/
 */

#include <iostream>
using namespace std;

namespace zero_one_package {
    const int V = 1010;
    int dp[V];

    int main() {
        int n, v;
        cin >> n >> v;
        while (n --) {
            int vi, wi;
            cin >> vi >> wi;
            for (int i = v; i >= vi; i --) dp[i] = max(dp[i], dp[i - vi] + wi);
        }
        cout << dp[v];
        return 0;
    }

}
