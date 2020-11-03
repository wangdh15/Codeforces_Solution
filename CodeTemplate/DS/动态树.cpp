/**
 *
 * 动态树，相当于在树链剖分的基础上，添加了动态的操作。
 * 每一个链用一个Splay来进行维护
 *
 * https://www.luogu.com.cn/problem/P3690
 *
 *
 *
 */

#include <iostream>
using namespace std;

const int N = 1e5 + 10;


struct Node {
    int s[2], p, v;
    int sum, rev;
}tr[N];

int stk[N];

int n, m;

// 判断x是否是其所在链的Splay的根节点
bool isroot(int x) {
    int p = tr[x].p;
    return tr[p].s[0] != x && tr[p].s[1] != x;
}

void eval(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev = tr[x].rev ^ 1;
}

// 利用孩子信息跟新自己的信息
void pushup(int x) {
    tr[x].sum = tr[tr[x].s[0]].sum ^ tr[tr[x].s[1]].sum ^ tr[x].v;
}

// 向下传递懒标记
void pushdown(int x) {
    if (tr[x].rev) {
        eval(tr[x].s[0]);
        eval(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

// 将x向上旋转一层，这里注意根节点的父节点的信息不能够修改
void rotate(int x) {

    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[y].s[k]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y);
    pushup(x);

}

// 将x旋转到其所属的Splay的根
void splay(int x) {

    // 先将从根到x的这一条路径上节点的懒标记自上到下逐个向下传
    int tt = 0;
    // 这里的栈不能够用stack，因为splay操作会调用非常多次，用stack会直接超时
    stk[++ tt] = x; 
    int cur = x;
    while (!isroot(cur)) {
        cur = tr[cur].p;
        stk[ ++tt] = cur;
    }
    while (tt) {
        int node = stk[tt --];
        pushdown(node);
    }

    // 然后开始双层旋转操作
    while (!isroot(x)) {

        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y)) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }

}



// 建立一条x所在树的根节点到x的一个链
// 自底向上逐步将多个树拼接起来
// 最后再将x旋转到根节点
void access(int x) {

    int x_bak = x;
    int cur_son = 0;
    
    while (x) {
        splay(x);
        tr[x].s[1] = cur_son;
        pushup(x);
        cur_son = x;
        x = tr[x].p;
    }
    splay(x_bak);
}


// 将x变为原树的根节点
void makeroot(int x) {
    access(x);
    eval(x);
}

// 找到x所在树的根节点
int findroot(int x) {

    access(x); // 这个操作结束之后，x已经是其所在链的Splay的根了
    // 这个地方没有向下传懒标记，是因为下面的splay会将
    // 从左孩子到根的这个路径上的懒标记都向下传
    while (tr[x].s[0]) x = tr[x].s[0];
    splay(x);
    return x;
}


// 将x和y之间的路径抽出来，用一个splay来进行维护
void split(int x, int y) {

    makeroot(x);
    access(y);

}

// 如果x和y不联通，则将x和y之间连一条边
void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;  // 将x所在的树搭到y所在的树上面
}


void cut(int x, int y) {

    makeroot(x);
    // 这三个条件缺一不可，必须确保xy之间有边，
    // 那么将x转到根节点之后，y是x的后继，就必须满足下面三个条件的所有
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {  
        tr[x].s[1] = 0;
        tr[y].p = 0;
        pushup(x);
    }
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> tr[i].v;
        tr[i].sum = tr[i].v;
    }

    int op;
    int x, y;

    while (m --) {

        cin >> op >> x >> y;
        if (op == 0) {
            split(x, y);
            cout << tr[y].sum << '\n';
        } else if (op == 1) {
            link(x, y);

        } else if (op == 2) {
            cut(x, y);
        } else {
            splay(x);
            tr[x].v = y;
            pushup(x);
        }

    }
    return 0;
}

