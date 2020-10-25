/**
 * Treap = Tree + Heap,同时满足二叉搜索树和堆的性质
 *
 * https://www.luogu.com.cn/problem/P3369
 *
 */

#include <iostream>
using namespace std;

constexpr int N = 1e5 + 5;
constexpr int INF = 1e8;

struct Node {
    int l, r;  // 表示左右孩子的编号
    int key, val; // key表示二叉树的关键字，val表示堆的关键字
    int cnt, size; // cnt表示当前关键字的个数，size表示以当前节点为根的子树的大小
} tr[N];

int root, idx;

void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int get_node(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

// 右旋操作
void zig(int &p) {

    int q = tr[p].l;
    tr[p].l = tr[q].r;
    tr[q].r = p;
    pushup(p);
    pushup(q);
    p = q;
}

// 左旋操作
void zag(int &p) {

    int q = tr[p].r;
    tr[p].r = tr[q].l;
    tr[q].l = p;
    pushup(p);
    pushup(q);
    p = q;
}

// 初始化操作
void init() {
    root = get_node(-INF);
    get_node(INF);
    tr[1].r = 2;
    pushup(root);
    if (tr[1].val < tr[2].val) zag(root); // 如果不满足堆的性质，则进行旋转调整
}

// 插入一个元素
void insert(int &p, int key) {
    if (!p) {
        p = get_node(key);
    }
    else {
        if (tr[p].key == key) {
            tr[p].cnt ++;
        } else if (tr[p].key < key) {
            insert(tr[p].r, key);
            if (tr[p].val < tr[tr[p].r].val) zag(p);

        } else {
            insert(tr[p].l, key);
            if (tr[p].val < tr[tr[p].l].val) zig(p);
        }
    }
    pushup(p);
}


// 删除一个元素
void erase(int &p, int key) {
    if (!p) return ;
    else if (tr[p].key == key) {
        if (tr[p].cnt > 1) tr[p].cnt --;

        else if (!tr[p].l && !tr[p].r) p = 0;

        else {

            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                zig(p);
                erase(tr[p].r, key);
            } else {
                zag(p);
                erase(tr[p].l, key);
            }
        }
    } else if (tr[p].key < key) {
        erase(tr[p].r, key);
    } else if (tr[p].key > key) {
        erase(tr[p].l, key);
    }
    pushup(p);
}

// 通过值找排名
int get_rank_by_key(int p, int key) {
    if (tr[p].key == key) return tr[tr[p].l].size + 1;
    else if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
    else return get_rank_by_key(tr[p].r, key) + tr[tr[p].l].size + tr[p].cnt;
}

// 通过排名找值
int get_key_by_rank(int p, int rank) {
    if (tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);
    else if (tr[tr[p].l].size + tr[p].cnt < rank) return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
    else return tr[p].key;
}

// 得到前驱
int get_prev(int p, int key) {
    if (!p) return -INF;
    if (tr[p].key >= key) return get_prev(tr[p].l, key);
    else return max(tr[p].key, get_prev(tr[p].r, key));
}

// 得到后继
int get_next(int p, int key) {
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    else return min(tr[p].key, get_next(tr[p].l, key));
}

int main() {

    int n;
    cin >> n;
    init();
    while (n --) {
        int op, x;
        cin >> op >> x;
        if (op == 1) insert(root, x);
        else if (op == 2) erase(root, x);
        else if (op == 3) cout << get_rank_by_key(root, x) - 1 << '\n';
        else if (op == 4) cout << get_key_by_rank(root, x + 1) << '\n';
        else if (op == 5) cout << get_prev(root, x) << '\n';
        else cout << get_next(root, x) << '\n';
    }
    return 0;
}

