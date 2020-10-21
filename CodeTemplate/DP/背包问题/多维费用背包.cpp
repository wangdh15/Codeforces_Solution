//
// Created by wangdh on 2020/10/21.
//

/*
 * 多维费用背包
 * 和01背包相同，只不过限制条件扩充为了多维
 * https://www.acwing.com/problem/content/8/
 */
#include <iostream>
using namespace std;

namespace multi_dimension_package {
    constexpr int V = 110, M = 110;
    int dp[V][M];

    int main() {

        int n, v, m;
        cin >> n >> v >> m;
        while (n--) {
            int vi, mi, wi;
            cin >> vi >> mi >> wi;
            for (int i = v; i >= vi; i--) {
                for (int j = m; j >= mi; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - vi][j - mi] + wi);
                }
            }
        }
        cout << dp[v][m];
        return 0;
    }
}
