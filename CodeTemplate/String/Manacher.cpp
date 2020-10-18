//
//
// Created by wangdh on 2020/10/18.
//

#include <iostream>
#include <vector>
using namespace std;

namespace Manacher {
    // 得到以s[i]为中心的且长度为奇数的最长回文串半径
    vector<int> getd1(string &s) {
        int n = s.size();
        vector<int> d1(n, 1);
        int l = 0, r = -1;
        for (int i = 0; i < n; i ++) {
            if (i <= r) d1[i] = min(d1[l + r - i], r - i + 1);
            while (i + d1[i] < n && i - d1[i] >= 0 && s[i + d1[i]] == s[i - d1[i]]) d1[i] ++;
            if (i + d1[i] - 1 > r) l = i - d1[i] + 1, r = i + d1[i] - 1;
        }
        return d1;
    }

// 得到以s[i]为中心的且长度为偶数的最长回文串半径，s[i] 在中间两个字符的偏后的位置
// 偶数长度的情况比奇数长度的要复杂，需要仔细分析
    vector<int> getd2(string &s) {
        int n = s.size();
        vector<int> d2(n, 0);
        int l = 0, r = -1;
        for (int i = 0; i < n; i ++) {
            if (i <= r) d2[i] = min(r - i + 1, d2[l + r - i + 1]);
            while (i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i + d2[i]] == s[i - d2[i] - 1]) d2[i] ++;
            if (i + d2[i] - 1 > r) l = i - d2[i], r = i + d2[i] - 1;
        }
        return d2;
    }

    // 通过在字符串中增加分隔符，从而达到统一处理的效果
    // 返回的二维数组，第一个是d1, 第二个是d2
    vector<vector<int>> getd(string &s) {
        string tmp = "";
        for (auto x : s) {
            tmp += '#';
            tmp += x;
        }
        int n = tmp.size();
        vector<int> res(n, 1);
        int l = 0, r = -1;
        for (int i = 0; i < n; i ++) {
            if (i <= r) res[i] = min(r - i + 1, res[l + r - i]);
            while (i + res[i] < n && i - res[i] >= 0 && tmp[i + res[i]] == tmp[i - res[i]]) res[i] ++;
            if (i + res[i] - 1 > r) l = i - res[i] + 1, r = i + res[i] - 1;
        }
        vector<vector<int>> ans(2, vector<int>(n / 2));
        for (int i = 0; i < n; i ++) {
            if (i & 1) ans[0][i / 2] = (res[i] + 1) / 2;
            else ans[1][i / 2] = res[i] / 2;
        }
        return ans;
    }

    int main() {

        string s;
        cin >> s;
        vector<int> l = getd1(s);
        vector<int> r = getd2(s);
        int ans = 0;
        for (auto x : l) ans = max(ans, x);
        for (auto x : r) ans = max(ans, x);
        cout << ans;
        return 0;
    }
}

