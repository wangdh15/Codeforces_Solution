//
// Created by wangdh on 2020/10/23.
//


/**
 * 可持久化Trie：核心思想是，在插入一个新的字符串的时候，对于这个字符串上的每个路径，都必须是新开的点，其它路径继承前面的节点。
 * 为什么要新开节点，这样是为了不破坏前面版本的结构。如果直接在前面版本上面进行加点的话，修改的内容从前面版本的根节点就可见了。
 * 所以新的路径要完全新开一个节点。其它继承前一个历史版本。
 *
 * 在处理每个节点的时候，先将上一个版本的所有孩子赋值，在新开节点来覆盖。
 *
 * https://www.acwing.com/problem/content/258/
 */
#include <iostream>
using namespace std;

namespace Trie_Persistence {
    constexpr int N = 6e5 + 10;
    int tr[N * 24][2], latest[N * 24];

    int root[N], s[N], idx;
    int n, m;

    // 插入操作，如果之前存在一个相同的路径，则需要将这个路径进行复制，同时保证其他的的都指向之前的路径
    void insert(int i, int k, int p, int q) {
        if (k < 0) {
            latest[q] = i;
            return ;
        }
        int cur = (s[i] >> k) & 1;
        // 赋值上一个版本的节点
        tr[q][0] = tr[p][0];
        tr[q][1] = tr[p][1];

        // 新开一个节点来覆盖
        tr[q][cur] = ++idx;
        insert(i, k - 1, tr[p][cur], tr[q][cur]);
        latest[q] = max(latest[tr[q][0]], latest[tr[q][1]]);  // 每棵树记录这个数的叶子节点中最大的id
    }

    // 查询操作
    int query(int cur, int val, int k, int limit) {
        if (k < 0) return s[latest[cur]] ^ val;
        int a = (val >> k) & 1;
        if (latest[tr[cur][a ^ 1]] >= limit)
            return query(tr[cur][a ^ 1], val, k - 1, limit);
        else
            return query(tr[cur][a], val, k - 1, limit);
    }

    int main() {

        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        latest[0] = -1;
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) {
            int x;
            cin >> x;
            s[i] = s[i - 1] ^ x;
            root[i] = ++idx;
            insert(i, 23, root[i - 1], root[i]);
        }

        while (m --) {
            string op;
            cin >> op;
            if (op == "A") {
                int x;
                cin >> x;
                n++;
                s[n] = s[n - 1] ^ x;
                root[n] = ++idx;
                insert(n, 23, root[n - 1], root[n]);
            } else {
                int l, r, x;
                cin >> l >> r >> x;
                cout << query(root[r - 1], s[n] ^ x, 23, l - 1) << '\n';
            }
        }
        return 0;
    }
}


