//
// Created by wangdh on 2020/10/22.
//

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;


/**
 * 自己手撕二分
 */
namespace self_binary_search {

    constexpr int N = 1e5 + 10;
    int rec[N];

    int find(int a) {
        int l = 0, r = N - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (rec[mid] >= a) r = mid - 1;
            else l = mid;
        }
        return l;
    }

    int main() {

        int n;
        int ans = 1;

        memset(rec, 0x3f, sizeof rec);
        rec[0] = -2e9;
        cin >> n;
        while (n --) {
            int x;
            cin >> x;
            int idx = find(x);
            ans = max(ans, idx + 1);
            rec[idx + 1] = min(x, rec[idx + 1]);
        }
        cout << ans;
        return 0;
    }
}

/**
 * 使用stl自带的二分函数
 */
namespace std_lower_bound {
    constexpr int N = 1e5 + 10;
    int main() {

        int n;
        int ans = 1;

        vector<int> rec(N, 2e9);
        rec[0] = -2e9;
        cin >> n;
        while (n --) {
            int x;
            cin >> x;
            int idx = lower_bound(rec.begin(), rec.end(), x) - rec.begin() - 1;
            ans = max(ans, idx + 1);
            rec[idx + 1] = min(x, rec[idx + 1]);
        }
        cout << ans;
        return 0;
    }
}
