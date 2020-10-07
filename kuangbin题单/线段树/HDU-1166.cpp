
// Problem: 敌兵布阵
// Contest: Virtual Judge - HDU
// URL: https://vjudge.net/problem/HDU-1166
// Memory Limit: 32 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
//#pragma GCC optimize(3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC target("sse3","sse2","sse")
//#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
//#pragma GCC target("f16c")
//#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
//#pragma GCC diagnostic error "-fwhole-program"
//#pragma GCC diagnostic error "-fcse-skip-blocks"
//#pragma GCC diagnostic error "-funsafe-loop-optimizations"
//#pragma GCC diagnostic error "-std=c++14"

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <cstdio>

// 时间够不要用unordered_map，unordered_set
// 不然会被CF大佬根据STL源码出的数据给hack掉
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
// 常用操作的简写
#define PB push_back
#define PF push_front
#define se second
#define fi first
#define sz(x) ((int)x.size())
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define REP(x, l, u) for(int x = l; x <= u; x++)
#define RREP(x, u, l) for(int x = u; x >= l; x--)
#define sqr(x) (x * x)





/*
 * 输出输出优化
 */
void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}


/******************
 * 代码开始
 * **************
 */

//#define  duipai
//#define kickstart
#define custom
#define multiTask

/*
 * 数据初始定义
 */

int T;
int n;
const int N = 5e4 + 10;
class Node {
public:
	int l, r;
	int s;
};

Node tr[4 * N];
int q[N];

void pushup(int u) {
	tr[u].s = tr[u << 1].s + tr[u << 1 | 1].s;
}

void build(int u, int l, int r) {
	tr[u].l = l;
	tr[u].r = r;
	if (l == r) tr[u].s = q[l];
	else {
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
}

int query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) return tr[u].s;
	int mid = tr[u].l + tr[u].r >> 1;
	if (l > mid) return query(u << 1 | 1, l, r);
	if (r <= mid) return query(u << 1, l, r);
	int tmp = 0;
	tmp += query(u << 1, l, r);
	tmp += query(u << 1 | 1, l, r);
	return tmp;
} 

void modify(int u, int x, int v) {
	if (tr[u].l == tr[u].r) tr[u].s += v;
	else {
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) modify(u << 1, x, v);
		else modify(u << 1 | 1, x, v);
		pushup(u);
	}
}

// 每个测试数据的方法
void solve(int t) {
	cin >> n;
	REP(i, 1, n) cin >> q[i];
	build(1, 1, n);
	cout << "Case " << t << ":" << endl;
	// REP(i, 1, 4 * n) {
		// printf("%d %d %d %d\n", i, tr[i].l, tr[i].r, tr[i].s);
	// }
	// printf("%d\n", query(1, 1, 1));
	char op[10];
	while (true) {
		scanf("%s", op);
		if (op[0] == 'E') return;
		int a, b;
		cin >> a >> b;
		if (op[0] == 'Q') {
			cout << query(1, a, b) << endl;
		} else if (op[0] == 'A') {
			modify(1, a, b);
		} else if (op[0] == 'S') {
			modify(1, a, -b);
		}
	}
	return;
}

#ifdef custom
int main() {
    io();

#ifdef multiTask
    cin >> T;
    REP(t, 1, T)
#endif

    solve(t);
    return 0;
}
#endif

#ifdef duipai
int main() {
    for(int T = 0; T < 10000; ++T) {
        system("./random > ./data.in");
        double st = clock();
        system("./sol < ./data.in > ./data.ans");
        double et = clock();
        system("./bf < ./data.in > ./data.out");
        if(system("diff ./data.out ./ data.ans")) {
            puts("Wrong Answer\n");
            return 0;
        } else {
            printf("Accepted, 测试点 #%d, 用时 %.0lfms\n", T, et - st);
        }
    }
    return 0;
}
#endif


