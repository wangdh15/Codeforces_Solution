//
// Created by wangdh on 2020/10/8.
//
#include <iostream>
#include <cstring>
using namespace std;


namespace floyd {
    const int N = 210;
    int g[N][N];
    int n, m, Q;

    void floyd() {
        for (int k = 1; k <= n; k ++) {
            for (int i = 1; i <= n; i ++) {
                for (int j = 1; j <= n; j ++) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }

    int main() {

        cin >> n >> m >> Q;
        memset(g, 0x3f, sizeof g);   // 其它初始化为正无穷
        for (int i = 1; i <= n; i ++) g[i][i] = 0;  // 自己到自己初始化为0
        while (m --) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a][b] = min(g[a][b], c);
        }
        floyd();
        while (Q --) {
            int a, b;
            cin >> a >> b;
            if (g[a][b] >= 0x3f3f3f3f / 2) cout << "impossible" << endl;  // 由于可能存在负权边，所以这里判断一个阈值
            else cout << g[a][b] << endl;
        }
        return 0;

    }
}

