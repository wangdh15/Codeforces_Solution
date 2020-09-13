[toc]

### 1. Kefa and Park

[原题链接]()

![image-20200913233610656](images/01.png)

#### 解题思路

直接dfs即可。在路径上需要记录一下到每个位置的时候，其所在的连续的猫的个数。

#### C++代码

```c++
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
vector<int> edges[N];
bool cat[N];
int n, m;
int ans = 0;
vector<int> path;


void dfs(int cur, int fa) {
    if (edges[cur].size() == 1 && edges[cur][0] == fa) {
        ans ++;
        return;
    }
    for (auto x : edges[cur]) {
        if (x == fa) continue;
        if (cat[x]) {
            if (path.back() + 1 > m) continue;
            else {
                path.push_back(path.back() + 1);
                dfs(x, cur);
                path.pop_back();
            }
        } else {
            path.push_back(0);
            dfs(x, cur);
            path.pop_back();
        }
    }
}

int main() {

    memset(cat, false, sizeof cat);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> cat[i];
    for (int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    path.push_back(cat[1]);
    dfs(1, -1);
    if (m == 0 && cat[1]) {
        cout << 0;
        return 0;
    }
    cout << ans;
    return 0;
}
```

