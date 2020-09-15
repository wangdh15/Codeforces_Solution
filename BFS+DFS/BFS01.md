[toc]

### 1. Maze

[原题链接](https://codeforces.com/problemset/problem/377/A)

![image-20200915151809913](images/01.png)

#### 解题思路

相当于给定一个连通图，然后要求从这个图中去掉`K`个点，保证去掉之后剩下的图还是联通的。

逆过来思考，首先从图中任意一点开始，使用深搜或者广搜，当搜到了`N - K`个点之后，说明这些点是联通的，然后将剩下的点删除即可。

#### C++代码

```c++
#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 510;
char q[N][N];
int n, m, k;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int main() {

    cin >> n >> m >> k;
    int x, y;
    bool flag = false;
    int empty = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> q[i][j];
            if (q[i][j] == '.') {
                empty ++;
                if (!flag) {
                    x = i;
                    y = j;
                    flag = true;
                }
            }
        }
    }
    queue<PII> qe;
    qe.push({x, y});
    int cnt = 1;
    q[x][y] = 'A';
    bool ok = false;
    if (cnt < empty - k) {
        while (!qe.empty()) {
            auto ele = qe.front();
            qe.pop();
            x = ele.first, y = ele.second;
            for (int i = 0; i < 4; i ++) {
                int xx = x + dx[i], yy = y + dy[i];
                if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
                if (q[xx][yy] == 'A' || q[xx][yy] == '#') continue;
                cnt++;
                q[xx][yy] = 'A';
                if (cnt == empty - k) {
                    ok = true;
                    break;
                }
                qe.push({xx, yy});
            }
            if (ok) break;
        }
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (q[i][j] == 'A') cout << '.';
            else if (q[i][j] == '.') cout << 'X';
            else cout << q[i][j];
        }
        cout << endl;
    }
    return 0;
}
```





