//
// Created by wangdh on 2020/10/22.
//

/**
 * 最长公共子序列问题
 */

#include <iostream>
using namespace std;

namespace common_subseq {
    constexpr int N = 1010;

    int dp[N][N];

    int main() {

        int n, m;
        string a, b;
        cin >> n >> m >> a >> b;
        a = " " + a;
        b = " " + b;
        for (int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++) {
                dp[i][j] = max(dp[i-1][j], dp[i][j - 1]);
                if (a[i] == b[j]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            }
        }
        cout << dp[n][m];
        return 0;

    }
}


