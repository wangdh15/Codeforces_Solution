//
// Created by wangdh on 2020/9/28.
//
#include <string>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
int ne[N];

void kmp(string &s, string &p) {
    int n = s.size();
    int m = p.size();
    s = " " + s;
    p = " " + p;
    memset(ne, 0, sizeof ne);

    // 求next数组
    int j = 0;
    for (int i = 2; i <= m; i ++) {
        while (j && p[j + 1] != p[i]) j = ne[j];
        if (p[j + 1] == p[i]) j ++;
        ne[i] = j;
    }

    // 进行匹配
    j = 0;
    for (int i = 1; i <= n; i ++) {
        while (j && p[j + 1] != s[i]) j = ne[j];
        if (p[j + 1] == s[i]) j ++;
        if (j == m) {
            cout << i - j << " ";
            j = ne[j];
        }
    }
}

