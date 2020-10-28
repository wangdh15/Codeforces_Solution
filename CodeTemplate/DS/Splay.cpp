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

int root, idx;
int n, m;

void pushup(int u) {
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

// 对x进行旋转操作
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i <= n + 1; i ++) insert(i);


}

