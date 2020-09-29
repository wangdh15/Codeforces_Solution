//
// Created by wangdh on 2020/9/28.
//

#include <iostream>
using namespace  std;

namespace prefixOne{

    // 一维前缀和
    const int N = 2e5 + 10;
    long long q[N], tmp[N];

    void init() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> q[i];
            q[i] += q[i-1];
        }
    }

    long long query(int l, int r) {
        return q[r] - q[l - 1];
    }

}

// 二维前缀和

namespace prefixTwo {

    const int N = 1010;
    int q[N][N];

    void init() {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= m; j ++) {
                cin >> q[i][j];
                q[i][j] += q[i-1][j] + q[i][j - 1] - q[i-1][j-1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        return q[x2][y2] - q[x2][y1 - 1] - q[x1 -1][y2] + q[x1 - 1][y1 - 1];
    }

}


// 一维差分
namespace diffOne{

    // 一维前缀和
    const int N = 2e5 + 10;
    long long q[N], tmp[N];

    void init() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> tmp[i];
            q[i] = tmp[i] - tmp[i - 1];
        }
    }

    void add(int l, int r, int c) {
        q[l] += c;
        q[r + 1] -= c;
    }
}

// 二维差分

namespace diffTwo {

    const int N = 1010;
    int q[N][N], tmp[N][N];
    int n, m;

    // 初始化
    void init() {
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= m; j ++) {
                cin >> tmp[i][j];
                q[i][j] = tmp[i][j] + tmp[i-1][j-1] - tmp[i-1][j] - tmp[i][j-1];
            }
        }
    }

    // 修改区间
    void edit(int x1, int y1, int x2, int y2, int c) {
        q[x1][y1] += c;
        q[x1][y2 + 1] -= c;
        q[x2 + 1][y1] -= c;
        q[x2 + 1][y2 + 1] += c;
    }

    // 修改完复原
    void out() {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= m; j ++) {
                q[i][j] += q[i-1][j] + q[i][j - 1] - q[i-1][j-1];
                cout << q[i][j] << " ";
            }
            cout << endl;
        }
    }
}

