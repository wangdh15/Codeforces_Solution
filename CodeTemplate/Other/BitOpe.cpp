//
// Created by wangdh on 2020/9/28.
//

namespace bitope{

    // 返回x的二进制表示中的1的个数
    int ones(int x) {
        int ans = 0;
        while (x) {
            ans ++;
            x &= (x - 1);
        }
        return ans;
    }

    // 返回最后一个1bit所代表的数
    int lowbit(int x) { return x & (-x); }

}