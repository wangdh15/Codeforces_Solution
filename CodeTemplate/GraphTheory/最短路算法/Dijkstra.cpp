//
// Created by wangdh on 2020/10/8.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

namespace dijkstra {

    typedef pair<int,int> PII;
    const int N = 150010;
    vector<PII> g[N];
    int n, m;
    int dis[N];
    int dijkstra() {
        memset(dis, 0x3f, sizeof dis);
        priority_queue<PII, vector<PII>, greater<PII>> heap;
        dis[1] = 0;
        heap.push({0, 1});
        while (heap.size()) {
            // 每个节点弹出的时候，其dis数组中存储的就是到这个节点的最短路
            auto ele = heap.top();
            heap.pop();
            int node = ele.second, di = ele.first;
            if (node == n) return dis[n];
            for (auto x : g[node]) {
                int nn = x.first, dd = x.second;
                if (dis[nn] > dis[node] + dd) {
                    dis[nn] = dis[node] + dd;
                    heap.push({dis[nn], nn});
                }
            }
        }

        if (dis[n] == 0x3f3f3f3f) return -1;
        else return dis[n];
    }

    int main() {
        cin >> n >> m;
        while (m --) {
            int x, y, z;
            cin >> x >> y >> z;
            g[x].push_back({y, z});
        }
        cout << dijkstra() << endl;
        return 0;
    }

}
