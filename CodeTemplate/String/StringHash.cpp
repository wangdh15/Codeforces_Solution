//
// Created by wangdh on 2020/9/28.
//

#include <string>
using namespace std;

typedef unsigned long long ULL;
const int N = 1e5 + 10;
const int p1 = 131;
//const int p1 = 13331;
ULL S[N], P[N];

/**
 * 得到l, r闭区间的字符串的hash表示
 * @param l
 * @param r
 * @return
 */
ULL get(int l, int r) {
    return S[r] - S[l - 1] * P[r - l + 1];
}

/**
 * 初始化hash数组
 * @param s
 */
void init(string &s) {
    int n = s.size();
    s = " " + s;
    for (int i = 1; i <= n; i ++) {
        P[i] = P[i - 1] * p1;
        S[i] = S[i - 1] * p1 + s[i] - 'a';
    }
}
