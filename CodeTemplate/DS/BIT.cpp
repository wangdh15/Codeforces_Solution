//
// Created by wangdh on 2020/9/29.
//


/*
 * 树状数组
 */
namespace BIT{

    const int N = 1e5 + 10;
    int tr[N];
    int n;

    int lowbit(int a) {
        return a & (-a);
    }

    /*
     * 单点修改操作
     */
    void add(int x, int a) {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] += a;
    }

    /*
     * 查询操作
     */
    int query(int x) {
        int ans = 0;
        for (int i = x; i; i -= lowbit(i)) ans += tr[i];
        return ans;
    }


}
