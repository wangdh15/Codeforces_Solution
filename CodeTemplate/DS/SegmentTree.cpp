//
// Created by wangdh on 2020/9/29.
//


// 原题链接(最大区间公约数)：https://www.acwing.com/problem/content/description/247/
#include <iostream>
using namespace std;
typedef long long LL;

/**
 * 不涉及区间更新，没有懒标记
 */
namespace SegmentTree{

    const int N = 5e5 + 10;

    class Node{
    public:
        int l, r;
        LL sum;
        LL v;
        Node() {
            l = r = sum = v = 0;
        }

    };

    Node tr[4 * N];
    int n, m;
    LL q[N];


     LL gcd(LL a, LL b) {
         return b ? gcd(b, a % b) : a;
     }

    // pushup操作，孩子节点信息更新父节点信息
    void pushup(Node &a, Node &b, Node &c) {

        a.sum = b.sum + c.sum;
        a.v = gcd(b.v, c.v);

    }

    void pushup(int u) {
        pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }


    // 初始化线段树操作
    void build(int u, int l, int r) {

        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            tr[u].sum = q[l] - q[l - 1];
            tr[u].v = tr[u].sum;
            return;
        }

        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);

    }

    // 查询操作
    Node query(int u, int l, int r) {

        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        Node left, right, res;
        if (l <= mid) left = query(u << 1, l, r);
        if (r > mid) right = query(u << 1 | 1, l, r);
        pushup(res, left, right);
        return res;
    }

    // 单点修改操作
    void modify(int u, int x, LL a) {

        if (tr[u].l == tr[u].r && tr[u].l == x) {
            tr[u].v += a;
            tr[u].sum += a;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid) modify(u << 1, x, a);
            else modify(u << 1 | 1, x, a);
            pushup(u);
        }
    }


    int main() {

        cin >> n >> m;
        for (int i = 1; i <= n; i ++) cin >> q[i];

        build(1, 1, n);

        while (m --) {

            char op;
            cin >> op;
            if (op == 'Q') {
                int l, r;
                cin >> l >> r;
                int s = query(1, 1, l).sum, tmp = query(1, l + 1, r).v;
                cout << abs(gcd(s, tmp)) << endl;
            } else {
                int l, r;
                LL a;
                cin >> l >> r >> a;
                modify(1, l, a);
                if (r + 1 <= n) modify(1, r + 1, -a);
            }

        }
        return 0;

    }

}

/**
 * 涉及区间更新，使用懒标记，在查询的时候才会真的更新所有的节点
 * 原题链接(维护序列) : https://www.acwing.com/problem/content/1279/
 */
namespace SegmentTree2{

    const int N = 1e5 + 10;

    class Node{
    public:
        int l, r;
        int mul, add;  // 记录传到当前位置的懒标记
        int val;
        Node() : l(0), r(0), mul(1), add(0) {}

    };

    Node tr[N * 4];
    int q[N];

    int n, p;
    int m;


// 一个节点接受一个新的mul和add，更新自己的值，并维护自己的懒标记
    void eval(Node &u, int mul, int add) {

        u.val = ((LL)u.val * mul + (LL)(u.r - u.l + 1) * add) % p;
        u.mul = ((LL)u.mul * mul) % p;
        u.add = ((LL)u.add * mul + add) % p;

    }

    void pushup(int u) {

        tr[u].val = (tr[u << 1].val + tr[u << 1 | 1].val) % p;

    }


// 一个节点需要将自己的懒标记传到自己的孩子节点
    void pushdown(int u) {

        eval(tr[u << 1], tr[u].mul, tr[u].add);
        eval(tr[u << 1 | 1], tr[u].mul, tr[u].add);
        tr[u].mul = 1;
        tr[u].add = 0;

    }

    int query(int u, int l, int r) {

        if (tr[u].l >= l && tr[u].r <= r) return tr[u].val;  // 把自己全包了，则直接返回，不往下差
        else {   // 需要涉及到自己的一部分，则更新自己的孩子节点，然后再往下查
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            int ans = 0;
            if (l <= mid) ans += query(u << 1, l, r);
            ans %= p;
            if (r > mid) ans += query(u << 1 | 1, l, r);
            ans %= p;
            return ans;
        }
    }

    void modify(int u, int l, int r, int mul, int add) {

        if (tr[u].l >= l && tr[u].r <= r) {  // 自己的整个区间都需要修改，则直接eval当前区间即可，不需要再向下传
            eval(tr[u], mul, add);
            return;
        } else {  // 一部分区间修改，下pushdown，再pushup
            pushdown(u); // 先把懒标记传递下去
            int mid = tr[u].l + tr[u].r >> 1;
            if (l <= mid) modify(u << 1, l, r, mul, add);
            if (r > mid) modify(u << 1 | 1, l, r, mul, add);
            pushup(u); // 由于l, r可能不包含自己的全部，所以部分孩子节点更新了，得更新自己。
        }

    }

    void build(int u, int l, int r) {

        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            tr[u].val = q[l];
            return;
        } else {
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    int main() {

        cin >> n >> p;
        for (int i = 1; i <= n;  i++) cin >> q[i];
        build(1, 1, n);
        // for (int i = 1; i <= 4 * n; i ++) cout << tr[i].l << " " << tr[i].r << " " << tr[i].val << endl;
        cin >> m;
        while (m --) {

            int op;
            cin >> op;
            if (op == 1) {
                int t, g, c;
                cin >> t >> g >> c;
                modify(1, t, g, c, 0);
            } else if (op == 2) {
                int t, g, c;
                cin >> t >> g >> c;
                modify(1, t, g, 1, c);
            } else {

                int t, g;
                cin >> t >> g;
                cout << query(1, t, g) << endl;

            }

        }
        return 0;
    }
}
