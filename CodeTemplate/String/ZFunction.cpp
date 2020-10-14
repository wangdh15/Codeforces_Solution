//
// Created by wangdh on 2020/10/14.
//

/**
 * z函数，扩展KMP算法，z[i]表示s[i:n-1]和s的最长公共前缀的长度。时间复杂度为O(n)。内部每次while循环都会至少将r增加一
 * 功能：
 *    1. 求字符串p在字符串s中出现的位置，令t = p + "#" + s, 求t的z函数，然后从s的位置开始扫描，找到z函数值为p长度的位置，就是匹配的位置。
 *       所以可以用KMP的地方，也可以用z函数来进行求解。
 *
 * 练习题：
 *      https://codeforces.com/contest/432/problem/D
 * */

#include <vector>
#include <string>
using namespace std;

namespace z_func {
    const int N = 1e5 + 10;
    int z[N];

    /**
     * 输入字符串s，计算出其z函数的值
     * @param s
     */
    void z_function(string s) {
        int n = s.size();
        int l = 0, r = 0;
        for (int i = 1; i < n; i ++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
    }
}

