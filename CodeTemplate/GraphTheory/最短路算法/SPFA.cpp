//
// Created by wangdh on 2020/10/8.
//

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

namespace spfa {

    typedef pair<int, int> PII;
    const int N = 1e5 + 10;
    vector<PII> g[N];
    int dis[N];
    bool st[N];
    int cnt[N];
    int n, m;

    /**
     * SPFA求最短路
     * @return
     */
    int spfa() {
        memset(dis, 0x3f, sizeof dis);
        dis[1] = 0;
        queue<int> qe;
        qe.push(1);
        st[1] = true;
        while (qe.size()) {
            int node = qe.front();
            qe.pop();
            st[node] = false;
            for (auto x : g[node]) {
                int nn = x.first, dd = x.second;
                if (dis[nn] > dis[node] + dd) {
                    dis[nn] = dis[node] + dd;
                    if (!st[nn]) {
                        st[nn] = true;
                        qe.push(nn);
                    }
                }
            }
        }
        return dis[n];
    }

    /**
     * spfa 判断是否存在负环，其实也可以用bellman-ford来判断，进行n次松弛之后如果还有节点被更新，则说明存在负环
     * 使用spfa可以记录每个节点到源节点的最短路的边的条数，如果这个条数大于等于n则说明存在负环
     * @return
     */
    bool spfa2() {

        queue<int> qe;
        memset(st, true, sizeof st);  // 可以看做有一个超级源点，所有节点都和这个源点有一个权重为0的边相连
        for (int i = 1; i <= n; i ++) qe.push(i);
        while (qe.size()) {
            int node = qe.front();
            qe.pop();
            st[node] = false;
            for (auto x : g[node]) {
                int nn = x.first, dd = x.second;
                if (dis[nn] > dis[node] + dd) {
                    dis[nn] = dis[node] + dd;
                    cnt[nn] = cnt[node] + 1;
                    if (cnt[nn] >= n) return true;
                    if (!st[nn]) {
                        st[nn] = true;
                        qe.push(nn);
                    }
                }
            }
        }
        return false;
    }


    int main() {

        cin >> n >> m;
        while (m --) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
        }
        int res = spfa();
        if (res == 0x3f3f3f3f) cout << "impossible";
        else cout << res;
    }
}

