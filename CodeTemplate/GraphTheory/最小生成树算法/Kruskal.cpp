#include <iostream>
#include <queue>
using namespace std;

namespace kruskal {

    typedef pair<int, pair<int, int>> PIII;
    const int N = 1e5 + 10;
    int fa[N];
    int n, m;

    int find(int a) {
        return a == fa[a] ? a : fa[a] = find(fa[a]);
    }

    void kruskal() {
        priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
        while (m --) {
            int a, b, c;
            cin >> a >> b >> c;
            heap.push({c, {a, b}});
        }
        int res = 0;
        int cnt = 0;
        while (cnt < n - 1 && heap.size()) {
            auto ele = heap.top();
            heap.pop();
            int len = ele.first, a = ele.second.first, b = ele.second.second;
            int ffa = find(a), ffb = find(b);
            if (ffa == ffb) continue;
            res += len;
            cnt ++;
            fa[ffa] = ffb;
        }
        if (cnt == n - 1) cout << res;
        else cout << "impossible";
        return;

    }

    int main() {
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) fa[i] =  i;
        kruskal();
        return 0;
    }

}



