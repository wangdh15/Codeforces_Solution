/**
 * https://www.acwing.com/problem/content/957/
 *
 * Splay动态维护一个有序序列，而且可以像线段树那样，维护区间信息，利用懒标记
 */

#include <iostream>
using namespace std;

const int N = 5e5 + 10, INF = 1e9;

struct Node {
    int s[2], p;
    int v;
    int size;
    int ls, rs, ms, sum;
    bool rev, same;
    void init(int _p, int _v) {
        p = _p;
        v = _v;
        size = 1;
        rev = same = false;
        ls = rs = max(0, v);
        ms = sum = v;
        s[0] = s[1] = 0;
    }
}tr[N];

int pool[N];
int idx;
int n, m;
int q[N];
int root;


void pushup(int u) {

    auto &cur = tr[u];
    auto &lc = tr[tr[u].s[0]];
    auto &rc = tr[tr[u].s[1]];
    cur.size = lc.size + rc.size + 1;
    cur.sum = lc.sum + rc.sum + cur.v;
    cur.ls = max(lc.ls, lc.sum + rc.ls + cur.v);
    cur.rs = max(rc.rs, rc.sum + lc.rs + cur.v);
    cur.ms = max(max(lc.ms, rc.ms), lc.rs + rc.ls + cur.v);
}


void pushdown(int u) {

    auto &cur = tr[u];
    auto &lc = tr[tr[u].s[0]];
    auto &rc = tr[tr[u].s[1]];

    if (cur.same) {
        cur.same = cur.rev = false;
        lc.same = rc.same = true;
        if (tr[u].s[0]) lc.v = cur.v, lc.sum = lc.v * lc.size;
        if (tr[u].s[1]) rc.v = cur.v, rc.sum = rc.v * rc.size;
        if (cur.v > 0) {
            if (tr[u].s[0]) lc.ls = lc.rs = lc.ms = lc.sum;
            if (tr[u].s[1]) rc.ls = rc.rs = rc.ms = rc.sum;
        } else {
            if (tr[u].s[0]) lc.ls = lc.rs = 0, lc.ms = lc.v;
            if (tr[u].s[1]) rc.ls = rc.rs = 0, rc.ms = rc.v;
        }
    } else if (cur.rev) {
        cur.rev = false;
        lc.rev = !lc.rev;
        rc.rev = !rc.rev;
        if (tr[u].s[0]) swap(lc.ls, lc.rs), swap(lc.s[0], lc.s[1]);
        if (tr[u].s[1]) swap(rc.ls, rc.rs), swap(rc.s[0], rc.s[1]);
    }
}


void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[y].s[k]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y);
    pushup(x);
}


void splay(int x, int k) {
    while (tr[x].p != k) {

        int y = tr[x].p,  z = tr[y].p;
        if (z != k) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}




int build(int l, int r, int p) {

    if (l > r) return 0;
    int u = pool[idx --];
    int mid = l + r >> 1;
    tr[u].init(p, q[mid]);
    tr[u].s[0] = build(l, mid - 1, u);
    tr[u].s[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}


int get_node_by_pos(int pos) {
    int u = root;
    while (u) {

        pushdown(u);
        if (tr[tr[u].s[0]].size >= pos) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == pos) return u;
        else pos -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];

    }
    return -1;
}

void del(int u) {
    if (tr[u].s[0]) del(tr[u].s[0]);
    if (tr[u].s[1]) del(tr[u].s[1]);
    pool[++idx] = u;
}


void debug(int u) {
    if (tr[u].s[0]) debug(tr[u].s[0]);
    cout << tr[u].v << " ";
    if (tr[u].s[1]) debug(tr[u].s[1]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> q[i];
    for (int i = 1; i < N; i ++) pool[i] = i;
    idx = N - 1;
    tr[0].ms = q[0] = q[n + 1] = -INF;
    root = build(0, n + 1, 0);

//    debug(root);

    string op;
    int pos, tot, c;
    while (m --) {
        cin >> op;
        if (op == "INSERT") {

            cin >> pos >> tot;
            for (int i = 1; i <= tot; i ++) cin >> q[i];
            int l = get_node_by_pos(pos + 1), r = get_node_by_pos(pos + 2);
            splay(l, 0), splay(r, l);
            tr[r].s[0] = build(1, tot, r);
            pushup(r);
            pushup(l);

        } else if (op == "DELETE") {

            cin >> pos >> tot;
            int l = get_node_by_pos(pos), r = get_node_by_pos(pos + tot + 1);
            splay(l, 0), splay(r, l);
            del(tr[r].s[0]);
            tr[r].s[0] = 0;
            pushup(r);
            pushup(l);

        } else if (op == "MAKE-SAME") {

            cin >> pos >> tot >> c;
            int l = get_node_by_pos(pos), r = get_node_by_pos(pos + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.same = true;
            son.v = c;
            son.sum = c * son.size;
            if (c > 0) son.ls = son.rs = son.ms = son.sum;
            else son.ls = son.rs = 0, son.ms = c;
            pushup(r);
            pushup(l);

        } else if (op == "REVERSE") {

            cin >> pos >> tot;
            int l = get_node_by_pos(pos), r = get_node_by_pos(pos + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.rev = !son.rev;
            swap(son.ls, son.rs);
            swap(son.s[0], son.s[1]);
            pushup(r);
            pushup(l);

        } else if (op == "GET-SUM") {

            cin >> pos >> tot;
            int l = get_node_by_pos(pos), r = get_node_by_pos(pos + tot + 1);
            splay(l, 0), splay(r, l);
            cout << tr[tr[r].s[0]].sum << '\n';

        } else {
            cout << tr[root].ms << '\n';
        }
    }

    return 0;
}
