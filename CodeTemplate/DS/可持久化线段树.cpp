//
// Created by wangdh on 2020/10/24.
//

/**
 * 可持久化线段树，核心思想还是对于进行修改的节点，都重新开一个节点，最终的效果是，新开了一个路径。
 * 模板题1： https://www.luogu.com.cn/problem/P3919
 * 模板题2：https://www.luogu.com.cn/problem/P3834
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 对每个版本都建一个版本的线段树即可。
// 查询的版本直接复用之前的根指针
namespace chairman_tree1 {
    constexpr int N = 1e6 + 10;
    struct Node {
        int lc, rc, v;
    }tr[N * 20];
    int root[N];
    int da[N];
    int idx;
    int ver;
    int n, m;

    int build(int l, int r) {
        int cur_idx = ++idx;
        if (l == r) tr[cur_idx].v = da[l];
        else {
            int mid = l + r >> 1;
            tr[cur_idx].lc = build(l, mid);
            tr[cur_idx].rc = build(mid + 1, r);
        }
        return cur_idx;
    }

    void modify(int p, int q, int l, int r ,int loc, int val) {
        if (l == r) tr[q].v = val;
        else {
            int mid = l + r >> 1;
            if (loc <= mid) {
                tr[q].rc = tr[p].rc;
                tr[q].lc = ++idx;
                modify(tr[p].lc, tr[q].lc, l, mid, loc, val);
            } else {
                tr[q].lc = tr[p].lc;
                tr[q].rc = ++idx;
                modify(tr[p].rc, tr[q].rc, mid + 1, r, loc, val);
            }
        }
    }

    int query(int cur, int l, int r, int loc) {
        if (l == r) return tr[cur].v;
        int mid = l + r >> 1;
        if (loc <= mid) return query(tr[cur].lc, l, mid, loc);
        else return query(tr[cur].rc, mid + 1, r, loc);
    }

    int main() {

        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) cin >> da[i];
        root[0] = build(1, n);

        while (m --) {
            int vi, op;
            cin >> vi >> op;
            if (op == 2) {
                int idx;
                cin >> idx;
                ++ver;
                root[ver] = root[vi];
                cout << query(root[vi], 1, n, idx) << '\n';
            } else {
                int x, y;
                cin >> x >> y;
                root[++ver] = ++idx;
                modify(root[vi], root[ver], 1, n, x, y);
            }
        }

        return 0;
    }
}

// 第二题的答案，相当于对两个版本的线段树直接做差，就得到了这两个版本之间修改的线段树，
// 然后查找到这个线段树中从左向右第k个1即可
namespace chairman_tree2 {
    using namespace std;

    const int N = 2e5 + 5;
    struct Node {
        int lc, rc, v;
    }tr[4 * N + N * 17];

    int root[N];
    vector<int> da;
    vector<int> bak;

    int idx;
    int n, m;

    int build(int l, int r) {
        int cur_idx = ++idx;
        if (l != r) {
            int mid = l + r >> 1;
            tr[cur_idx].lc = build(l, mid);
            tr[cur_idx].rc = build(mid + 1, r);
        }
        return cur_idx;
    }

    void modify(int p, int q, int loc, int l, int r) {
        if (l == r) {
            tr[q].v = tr[p].v + 1;
        } else {
            int mid = l +  r >> 1;
            if (loc <= mid) {
                tr[q].rc=  tr[p].rc;
                tr[q].lc = ++idx;
                modify(tr[p].lc, tr[q].lc, loc, l, mid);
                tr[q].v = tr[tr[q].lc].v + tr[tr[q].rc].v;
            } else {
                tr[q].lc = tr[p].lc;
                tr[q].rc = ++idx;
                modify(tr[p].rc, tr[q].rc, loc, mid + 1, r);
                tr[q].v = tr[tr[q].lc].v + tr[tr[q].rc].v;
            }
        }
    }

    int query(int p, int q, int l, int r, int k) {

        if (l == r) {
            return da[l];
        }
        else {
            int mid = l + r >> 1;
            if (tr[tr[q].lc].v - tr[tr[p].lc].v >= k) return query(tr[p].lc, tr[q].lc, l, mid, k);
            else return query(tr[p].rc, tr[q].rc, mid + 1, r, k - (tr[tr[q].lc].v - tr[tr[p].lc].v));
        }
    }


    int find(int a) {
        return lower_bound(da.begin(), da.end(), a) - da.begin();
    }

    int main() {

        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n >> m;
        for(int i = 0; i < n; i ++) {
            int x;
            cin >> x;
            da.push_back(x);
            bak.push_back(x);
        }
        sort(da.begin(), da.end());
        da.erase(unique(da.begin(), da.end()),da.end());
        root[0] = build(0, da.size() - 1);
        for (int i = 0; i < n; i ++) {
            root[i + 1] = ++idx;
            modify(root[i], root[i + 1], find(bak[i]),  0, da.size() - 1);
        }
        while (m --) {
            int l, r, k;
            cin >> l >> r >> k;
            cout << query(root[l - 1], root[r], 0, da.size() - 1, k) << '\n';
        }
        return 0;
    }
}


