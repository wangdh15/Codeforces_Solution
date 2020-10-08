//
// Created by wangdh on 2020/10/8.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;

namespace bellman_ford {

    const int N = 510;
    int dis[N];
    int dis_bak[N];
    vector<PII> g[N];
    int n, m, k;
    int bellman_ford() {

        memset(dis, 0x3f, sizeof dis);
        dis[1] = 0;
        for (int i = 1; i <= k; i ++) {   // 执行k次松弛操作
            memcpy(dis_bak, dis, sizeof dis);   //每次松弛操作都要将上一次的结果备份，避免链式更新
            for (int j = 1; j <= n; j ++) {
                for (auto x : g[j]) {
                    int node = x.first, dd = x.second;
                    if (dis[node] > dis_bak[j] + dd) {
                        dis[node] = dis_bak[j] + dd;
                    }
                }
            }
        }
        if (dis[n] >= 0x3f3f3f3f / 2) return -1;   //由于可能目标节点的距离被其相邻的节点松弛掉，所以这个地方需要判断一个阈值，而不是等于0x3f3f3f3f
        else return dis[n];
    }

    int main() {

        cin >> n >> m >> k;
        while (m --) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
        }

        int res = bellman_ford();
        if (res == -1) cout << "impossible";
        else cout << res;
        return 0;

    }
}
