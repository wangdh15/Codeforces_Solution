#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace topsort {
    const int N = 1e5 + 10;
    vector<int> g[N];
    int ind[N];
    int n, m;

    void topsort() {
        queue<int> qe;
        for (int i = 1; i <= n; i ++) {
            if (!ind[i]) qe.push(i);
        }
        vector<int> ans;
        while (qe.size()) {
            auto ele = qe.front();
            qe.pop();
            ans.push_back(ele);
            for (auto x : g[ele]) {
                ind[x] --;
                if (!ind[x]) qe.push(x);
            }
        }
        if (ans.size() == n) {
            for (auto x : ans) cout << x << " ";
        } else {
            cout << -1;
        }
    }

    int main() {

        cin >> n >> m;
        while (m --) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            ind[b] ++;
        }
        topsort();
        return 0;

    }
}

