#include <iostream>
#include <cstring>
using namespace std;

namespace Prim{
    const int N = 510;
    int dis[N];
    int n, m;
    int g[N][N];
    bool st[N];

    void prim() {

        memset(dis, 0x3f, sizeof dis);
        dis[1] = 0;
        int ans = 0;
        for (int j = 0; j < n; j ++) {
            int min_node = 0;
            for (int i = 1; i <= n; i ++) {
                if (!st[i] && (!min_node || dis[min_node] > dis[i])) min_node = i;
            }
            if (dis[min_node] == 0x3f3f3f3f) {
                cout << "impossible";
                return;
            }
            ans += dis[min_node];
            st[min_node] = true;
            for (int i = 1; i <= n; i ++) {
                if (!st[i] && dis[i] > g[min_node][i]) dis[i] = g[min_node][i];
            }
        }
        cout << ans;
        return;

    }

    int main() {
        cin >> n >> m;
        memset(g, 0x3f, sizeof g);
        while (m --) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a][b] = g[b][a] = min(g[a][b], c);
        }

        prim();

        return 0;
    }
}

