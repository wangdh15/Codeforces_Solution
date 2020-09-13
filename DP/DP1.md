[toc]

### 1. Boredom

[原题链接](https://codeforces.com/problemset/problem/455/A)

![image-20200913231324062](images/01.png)

#### 解题思路

考虑解决问题的顺序，由于所有的数字的大小在`1 - 1e5`之间，设`dp[i]`为考虑大小在`1 - i`范围的数的最大分数，则可以分为两类：

- 选`i`，则最大为`dp[i-2] + i * cnt[i]`
- 不选i，则最大为`dp[i-1]`

所以有`dp[i] = max(dp[i-1], dp[i-2] + i * cnt[i])`

最后输出`dp[100000]`即可。

#### C++代码

```c++
#include <iostream>
#include <cstring>
using namespace  std;

const int N = 1e5 + 10;
int cnt[N];
long long dp[N];
int ans = 0;
int n;

int main() {

    memset(cnt, 0, sizeof cnt);
    cin >> n;
    while (n --) {
        int a;
        cin >> a;
        cnt[a] ++;
    }
    dp[1] = cnt[1];
    for (int i = 2; i <= 1e5; i ++) dp[i] = max(dp[i-1], dp[i-2] + (long long)cnt[i] * i);
    cout << dp[100000];
    return 0;
}
```

### 2. Divisibility by Eight

[原题链接](https://codeforces.com/problemset/problem/550/C)

![image-20200913232244533](images/02.png)

#### 解题思路

方法1.考虑1000可以被8整除，所以只需要找位数为1， 2，3的是否存在被8整除的即可。然后可以分别扫描三次循环。时间复杂度为$O(n^3)$， $n$为长度。

方法2.动态规划。我们考虑长度为`i`的串的问题，那么如果其存在可以被8整除的方案，则可以分为两类：

- 方案中包含最后一个数字
- 方案中不包含最后一个数字

如果方案中包含最后一个数字，那么前面`i-1`个需要存在除8余`k`的方案，且`k * 10 + dig[i]`能够被8整除。

所以记录`dp[i][j]`, j取0-7表示前`i`个数字是否存在除8余j的方案，且还需要一个数组记录下来这个方案是谁。

然后进行状态转移即可。时间复杂度为`O(n)`

发现可以使用滚动数组进行优化。

#### C++代码

```c++
// 方法1
#include <iostream>
#include <vector>
using namespace std;


int work(string& s) {


    vector<int> digits;
    for (auto x : s) digits.push_back(x - '0');
    int n = digits.size();

    for (int i = 0; i < n; i ++) {
        if (digits[i] % 8 == 0) return digits[i];
        for (int j = i + 1; j < n; j ++) {
            if ((digits[i] * 2 + digits[j]) % 8 == 0) return digits[i] * 10 + digits[j];
            for (int k = j + 1; k < n; k ++) {
                if ((digits[i] * 4 + digits[j] * 2 + digits[k]) % 8 == 0) return digits[i] * 100 + digits[j] * 10 + digits[k];
            }
        }
    }
    return -1;
}


int main() {

    string s;
    cin >> s;
    int ans = work(s);
    if (ans == -1) cout << "NO";
    else {
        cout << "YES" << endl << ans;
    }
    return 0;

}

// 方法2
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
bool dp[N][8];
int pre[N][8];

int work(string& s) {


    vector<int> digits;
    for (auto x : s) digits.push_back(x - '0');
    int n = digits.size();
    dp[0][0] = true;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < 8; j ++) {
            if (j == 0) continue;
            else {
                if (dp[i][j]) {
                    dp[i + 1][j] = true;
                    pre[i + 1][j] = pre[i][j];
                }
            }

        }
        for (int j = 0; j < 8; j ++) {
            if (dp[i][j]) {
                int t = (j * 10 + digits[i]) % 8;
                if (!dp[i + 1][t]) {
                    dp[i + 1][t] = true;
                    pre[i + 1][t] = pre[i][j] * 10 + digits[i];
                }
            }
        }
        if (dp[i + 1][0]) return pre[i + 1][0];
        else dp[i + 1][0] = true;
    }
    return -1;

}


int main() {

    string s;
    cin >> s;
    int ans = work(s);
    memset(dp, false, sizeof dp);
    if (ans == -1) cout << "NO";
    else {
        cout << "YES" << endl << ans;
    }
    return 0;

}

// 方法2，滚动数组
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
bool dp[2][8];
int pre[2][8];

int work(string& s) {


    vector<int> digits;
    for (auto x : s) digits.push_back(x - '0');
    int n = digits.size();
    dp[0][0] = true;
    for (int i = 0; i < n; i ++) {
        dp[(i + 1) % 2][0] = false;
        for (int j = 0; j < 8; j ++) {
            if (j == 0) continue;
            else {
                if (dp[i % 2][j]) {
                    dp[(i + 1) % 2][j] = true;
                    pre[(i + 1) % 2][j] = pre[i % 2][j];
                }
            }

        }
        for (int j = 0; j < 8; j ++) {
            if (dp[i % 2][j]) {
                int t = (j * 10 + digits[i]) % 8;
                if (!dp[(i + 1) % 2][t]) {
                    dp[(i + 1) % 2][t] = true;
                    pre[(i + 1) % 2][t] = pre[i % 2][j] * 10 + digits[i];
                }
            }
        }
        if (dp[(i + 1) % 2][0]) return pre[(i + 1) % 2][0];
        else dp[(i + 1) % 2][0] = true;
    }
    return -1;

}


int main() {

    string s;
    cin >> s;
    int ans = work(s);
    memset(dp, false, sizeof dp);
    if (ans == -1) cout << "NO";
    else {
        cout << "YES" << endl << ans;
    }
    return 0;

}
```



