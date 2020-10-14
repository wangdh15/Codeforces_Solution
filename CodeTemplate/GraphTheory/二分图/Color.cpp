#include <iostream>
#include <vector>
using namespace std;

namespace color {
    const int N = 1e5 + 10;

    vector<int> g[N];
    int n, m;
    int color[N];

    bool dfs(int cur) {
        for (auto x : g[cur]) {
            if (color[x] == color[cur]) return false;
            if (!color[x]) {
                color[x] = 3 - color[cur];
                if (!dfs(x)) return false;
            }
        }
        return true;
    }

    int main() {

        cin >> n >> m;
        while (m --) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        bool flag = true;
        for (int i = 1; i <= n; i ++) {
            if (!color[i]) {
                color[i] = 1;
                if (!dfs(i)) {
                    flag = false;
                    break;
                }
            }
        }

        if (flag) cout << "Yes";
        else cout << "No";
        return 0;
    }
}

