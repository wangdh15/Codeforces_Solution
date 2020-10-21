//
// Created by wangdh on 2020/10/21.
//

/**
 * 多重背包问题
 * 每个物品的个数是有限的
 * https://www.acwing.com/problem/content/4/
 */

#include <iostream>
using namespace std;


/**
 * 朴素解法
 */
namespace multi_package_base {

    const int V = 110;
    int dp[V];
    int main() {
        int n, v;
        cin >> n >> v;
        while (n --) {
            int vi, wi, si;
            cin >> vi >> wi >> si;
            for (int i = v; i >= vi; i --) {
                for (int j = 1; j <= si && vi * j <= i; j ++) dp[i] = max(dp[i], dp[i - j * vi] + j * wi);
            }
        }
        cout << dp[v];
        return 0;
    }
}

/**
 * 二进制分解优化
 */
namespace multi_package_binary_optimization {
    #include <iostream>
    using namespace std;

    const int V = 2010;
    int dp[V];

    int main() {
        int n, v;
        cin >> n >> v;
        while (n --) {
            int vi, wi, si;
            cin >> vi >> wi >> si;
            int cur_cnt = 1;
            while (cur_cnt <= si) {
                si -= cur_cnt;
                for (int i = v; i >= cur_cnt * vi; i --) dp[i] = max(dp[i - cur_cnt * vi] + cur_cnt * wi, dp[i]);
                cur_cnt *= 2;
            }
            if (si) {
                for (int i = v; i >= si * vi; i --) dp[i] = max(dp[i], dp[i - si * vi] + si * wi);
            }
        }
        cout << dp[v];
        return 0;
    }
}

//TODO 单调队列优化

namespace multi_package_queue_optimization {

}
