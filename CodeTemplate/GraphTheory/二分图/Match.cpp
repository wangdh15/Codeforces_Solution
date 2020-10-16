//
// Created by wangdh on 2020/10/16.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

namespace HungaryAlgorithm  {

    const int N = 510;
    int match[N];
    int n1, n2, m;
    vector<int> g[N];
    bool st[N];


    bool find(int a) {
        for (auto x : g[a]) {
            if (st[x]) continue;  // 查看右边的点x是不是被访问过
            st[x] = true;
            if (!match[x] || find(match[x])) {  // 如果其没有对象，或者其对象可以再找到一个的话
                match[x] = a;
                return true;
            }
        }
        return false;
    }

    int main() {

        cin >> n1 >> n2 >> m;
        while (m --) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
        }

        int cnt = 0;
        for (int i = 1; i <= n1; i ++) {
            memset(st, false, sizeof st);
            if(find(i)) cnt ++;
        }
        cout << cnt;
        return 0;

    }
}



