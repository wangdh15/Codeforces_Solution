/**
 *https://www.acwing.com/problem/content/2716/
 * 核心操作就一个，合并两棵子树。
 * 删除操作转为将根左右两颗子树合并
 * 插入操作将插入元素新建一个节点，转为将两颗子树合并
 */

#include <iostream>
using namespace std;

const int N = 2e5 + 5;
int fa[N], root[N];
struct Node {
    int l, r;
    int v, h;
}tr[N];

int n, idx;

int cmp(int x, int y) {
    if (tr[x].v != tr[y].v) return tr[x].v < tr[y].v;
    else return x < y;
}

int find(int a) {
    return a == fa[a] ? fa[a] : fa[a] = find(fa[a]);
}

// 将两棵树合并的操作
int merge(int x, int y) {
    
    if (!x || !y) return x + y;  // 一个为空的话，直接返回另一个
    if (cmp(y, x)) swap(x, y); // 保证x是合并之后的根节点
    tr[x].r = merge(tr[x].r, y);
    if (tr[tr[x].l].h < tr[tr[x].r].h) swap(tr[x].l, tr[x].r);
    tr[x].h = tr[tr[x].r].h + 1;
    return x;

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i ++) fa[i] = i, root[i] = i;

    int op, a, x, y;
    while (n --) {
        cin >> op;
        if (op == 1) {
            cin >> a;
            tr[++idx] = {0, 0, a, 1};
        } else if (op == 2) {
            cin >> x >> y;
            x = find(x), y = find(y);
            if (x == y) continue;
            fa[x] = y;
            root[y] = merge(root[x], root[y]);
        } else if (op == 3) {
            cin >> x;
            cout << tr[root[find(x)]].v << '\n';
        } else {
            cin >> x;
            x = find(x);
            root[x] = merge(tr[root[x]].l, tr[root[x]].r);
        }
    }
    return 0;
}
