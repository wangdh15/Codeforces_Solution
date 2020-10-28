/**

 Splay, 通过灵活的旋转操作，能够动态维护区间信息，兼具线段树和平衡树的优势。

   https://www.luogu.com.cn/problem/P3391

 */
#include <iostream>
using namespace std;

constexpr int N = 1e5 + 10;

struct Node {
    int s[2];
    int pa;
    int v;
    bool flag;
    int size;
    void init(int _val, int _pa) {
        v = _val;
        pa = _pa;
        size = 1;
    }
};

typedef struct Node node;
node tr[N];

int root, idx = 1;
int n, m;

// 利用孩子节点信息更新父节信息。
void pushup(int u) {
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

// 将懒标记向下传
void pushdown(int u) {
    if (tr[u].flag) {
        swap(tr[u].s[0], tr[u].s[1]);
        tr[tr[u].s[0]].flag ^= 1;
        tr[tr[u].s[1]].flag ^= 1;
        tr[u].flag = 0;
    }
}

// 对x进行旋转操作，可以验证，不管对于左旋还是右旋，这个函数都是正确的
void rotate(int x) {
    int p = tr[x].pa, g = tr[p].pa;
    int k = tr[p].s[1] == x;  // k = 0表示x是p的左二子，1表示x是p的右儿子
    tr[g].s[tr[g].s[1] == p] = x, tr[x].pa = g;
    tr[p].s[k] = tr[x].s[k ^ 1], tr[tr[p].s[k]].pa = p;
    tr[x].s[k ^ 1] = p, tr[p].pa = x;
    pushup(x);
    pushup(p);
}

// 将x旋转到k下面
void splay(int x, int k) {

    while (tr[x].pa != k) {
        int p = tr[x].pa, g = tr[p].pa;
        if (g != k) {
            if ((tr[p].s[1] == x) ^ (tr[g].s[1] == x)) rotate(x);
            else rotate(p);
        }
        rotate(x);
    }
    if (!k) root = x;

}

// 插入操作
void insert(int v) {
    int u = root, p = 0;
    while (u) {
        p = u;
        u = tr[u].s[v > tr[u].v];
    }
    u = idx ++;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
}

// 获取当前序列中序遍历的第k个节点
int get_k(int k) {
    
    int u = root;
    while (true) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

void output(int u) {
    
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) cout << tr[u].v << " ";
    if (tr[u].s[1]) output(tr[u].s[1]);
    
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i <= n + 1; i ++) insert(i);
    while (m --) {
        int l, r;
        cin >> l >> r;
        l = get_k(l), r = get_k(r + 2);
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}

