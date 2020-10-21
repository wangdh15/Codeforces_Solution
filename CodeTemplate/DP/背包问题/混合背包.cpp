//
// Created by wangdh on 2020/10/21.
//

/*
 * 混合背包问题，三个类型各自用各自的方法即可。
 * https://www.acwing.com/problem/content/7/
 */

#include <iostream>
using namespace std;
namespace hybrid_package {

    constexpr int V = 1010;
    int dp[V];

    int main() {

        int n, v;
        cin >> n >> v;
        while (n --) {
            int vi, wi, t;
            cin >> vi >> wi >> t;
            if (t == -1) {
                for (int i = v; i >= vi; i --) dp[i] = max(dp[i], dp[i - vi] + wi); // 01背包
            } else if (t == 0) {
                for (int i = vi; i <= v; i ++) dp[i] = max(dp[i], dp[i - vi] + wi); // 完全背包
            } else {  // 分组背包
                int cur_cnt = 1;
                while (cur_cnt <= t) {
                    t -= cur_cnt;
                    for (int i = v; i >= cur_cnt * vi; i --) dp[i] = max(dp[i], dp[i - cur_cnt * vi] + cur_cnt * wi);
                    cur_cnt *= 2;
                }
                if (t) {
                    for (int i = v; i >= t * vi; i --) dp[i] = max(dp[i], dp[i - t * vi] + t * wi);
                }
            }
        }
        cout << dp[v];
        return 0;
    }
}