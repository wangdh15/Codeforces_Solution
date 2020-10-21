//
// Created by wangdh on 2020/10/21.
//

/**
 * 背包问题求具体方案
 * 为了方便，将所有物品逆序考虑
 * 当当前物品可以加入的时候，就将其加入。这样字典序才是最小的。
 */
#include <iostream>
#include <vector>
using namespace std;

namespace package_mini_method {

    constexpr int N = 1010;
    constexpr int V = 1010;
    int dp[N][V];
    int VI[N], WI[N];

    int main() {
        int n, v;
        cin >> n >> v;
        for (int i = 1; i <= n; i ++) {
            cin >> VI[i] >> WI[i];
        }
        for (int i = n; i >= 1; i --) {  // 所有物品逆序考虑
            int vi = VI[i], wi = WI[i];
            for (int j = 0; j <= v; j ++) {
                if (j < vi) dp[i][j] = dp[i+1][j];
                else dp[i][j] = max(dp[i+1][j-vi] + wi, dp[i+1][j]);
            }
        }
        int cur_v = v;
        for (int i = 1; i <= n; i ++) {  // 正向输出方案
            if (cur_v >= VI[i] && dp[i][cur_v] == dp[i+1][cur_v-VI[i]] + WI[i]) {
                cout << i << " ";
                cur_v -= VI[i];
            }
        }
        return 0;
    }
}
