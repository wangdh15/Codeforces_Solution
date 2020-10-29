/**
 * Splay模板，较为工程化的实现
 * https://www.acwing.com/problem/content/description/255/
 */

#include <iostream>
#include <vector>
using namespace std;

constexpr int N = 1e5 + 10;

class Node {
public:
    int s[2];
    int p;
    int k;
    int cnt, size;
    void init(int _k, int _p) {
        k = _k;
        p = _p;
        cnt = size = 1;
    }
};

class Splay {
public:
    static constexpr int INF = 2e9;

    Splay(int _max_nodes) :
        data(vector<Node>(_max_nodes)),
        root(0),
        idx(0) {
        // 插入哨兵元素
        _insert(-INF);
        _insert(INF);
    }

    void splay(int x, int k) {
        while (data[x].p != k) {
            int y = data[x].p, z = data[y].p;
            if (z != k) {
                if ( (data[y].s[1] == x) ^ (data[z].s[1] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        if (!k) root = x;
    }

    int get_rank_by_key(int key) {
        return _get_rank_by_key(key) - 1;
    }

    int get_key_by_rank(int rank) {
        return _get_key_by_rank(rank + 1);
    }

    int get_prev(int key) {
        return _get_prev(key);
    }

    int get_next(int key) {
        return _get_next(key);
    }

    void insert(int key) {_insert(key);}

    void erase(int key) {_erase(key);}

private:

    vector<Node> data;
    int root;
    int idx;

    // pushup操作，利用孩子信息更新自己的信息
    void pushup(int x) {
        data[x].size = data[data[x].s[0]].size + data[data[x].s[1]].size + data[x].cnt;
    }

    // pushdown 操作，在节点需要维护懒标记的时候向下传，需要自己实现
    void pushdown(int x) {
        return;
    }

    // 旋转操作，将x和其父亲进行旋转
    void rotate(int x) {

        int y = data[x].p, z = data[y].p;
        int k = data[y].s[1] == x;
        data[z].s[data[z].s[1] == y] = x, data[x].p = z;
        data[y].s[k] = data[x].s[k ^ 1], data[data[y].s[k]].p = y;
        data[x].s[k ^ 1] = y, data[y].p = x;
        pushup(y);
        pushup(x);
    }

    // 插入操作
    void _insert(int k) {
        int u = root, p = 0;
        while (u) {
            p = u;
            if (data[u].k == k) break;
            else u = data[u].s[k > data[u].k];
        }
        if (u) {
            data[u].cnt ++;
            pushup(u);
        } else {
            u = ++idx;
            if (p) data[p].s[k > data[p].k] = u;
            data[u].init(k, p);
        }
        splay(u, 0);
    }

    // 删除操作
    void _erase(int k) {
        int u = root;
        while (u) {
            if (data[u].k == k) break;
            else u = data[u].s[k > data[u].k];
        }
        if (!u) return;
        splay(u, 0);
        data[u].cnt --;
        if (data[u].cnt) {
            pushup(u);
            return;
        } else {
            if (data[u].s[0] && data[u].s[1]) {  // 将左子树的最大值转到根节点，然后将右子树放到其右孩子位置
                int t = data[u].s[0];
                data[t].p = 0;
                root = t;
                while (data[t].s[1]) t = data[t].s[1];
                splay(t, 0);
                data[t].s[1] = data[u].s[1];
                data[data[t].s[1]].p = t;
                pushup(t);
            } else {
                if (data[u].s[0]) {
                    root = data[u].s[0];
                    data[data[u].s[0]].p = 0;
                } else {
                    root = data[u].s[1];
                    data[data[u].s[1]].p = 0;
                }
            }
        }
    }

    // 通过值找排名
    int _get_rank_by_key(int k) {
        int u = root;
        int cur_rank = 0;
        while (u) {
            if (data[u].k == k) return cur_rank + data[data[u].s[0]].size + 1;
            else if (k < data[u].k) u = data[u].s[0];
            else cur_rank += data[data[u].s[0]].size + data[u].cnt, u = data[u].s[1];
        }
        return -1;
    }

    // 通过排名找值
    int _get_key_by_rank(int rank) {
        int u = root;
        while (u) {
            if (data[data[u].s[0]].size >= rank) u = data[u].s[0];
            else if (data[data[u].s[0]].size + data[u].cnt < rank) rank -= data[data[u].s[0]].size + data[u].cnt, u = data[u].s[1];
            else return data[u].k;
        }
    }

    // 找前驱，二分查找的思想
    int _get_prev(int k) {
        int ans;
        int u = root;
        while (u) {
            if (data[u].k >= k) u = data[u].s[0];
            else ans = data[u].k, u = data[u].s[1];
        }
        return ans;
    }

    // 找后继，二分查找的思想
    int _get_next(int k) {
        int ans;
        int u = root;
        while (u) {
            if (data[u].k <= k) u = data[u].s[1];
            else ans = data[u].k, u = data[u].s[0];
        }
        return ans;
    }

};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Splay splay(N);

    int n;
    cin >> n;

    while (n --) {
        int op, x;
        cin >> op >> x;
        if (op == 1) splay.insert(x);
        else if (op == 2) splay.erase(x);
        else if (op == 3) cout << splay.get_rank_by_key(x) << '\n';
        else if (op == 4) cout << splay.get_key_by_rank(x) << '\n';
        else if (op == 5) cout << splay.get_prev(x) << '\n';
        else cout << splay.get_next(x) << '\n';
    }
    return 0;
}

