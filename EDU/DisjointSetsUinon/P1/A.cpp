
// Problem: A. Disjoint Sets Union
// Contest: Codeforces - ITMO Academy: pilot course - Disjoint Sets Union - Step 1
// URL: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A
// Memory Limit: 256 MB
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
typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIII;
typedef pair<LL, int> PLI;
typedef pair<ULL, int> PUI;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<PII> VPII;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;
typedef priority_queue<int, vector<int>, greater<int>> isheap;
typedef priority_queue<int> ibheap;
typedef priority_queue<PII, vector<PII>, greater<PII>> piisheap;
typedef priority_queue<PII> piibheap;
typedef priority_queue<PIII, vector<PIII>, greater<PIII>> piiisheap;
typedef priority_queue<PIII> piiibheap;
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


// 给静态数组设值
#define setZE(x) memset(x, 0, sizeof x)
#define setPI(x) memset(x, 0x3f, sizeof x)
#define setMI(x) memset(x, -0x3f, sizeof x)


// lowbit操作，树状数组
#define lowbit(x) ((x)&(-(x)))

// 直接输出x的二进制表示中的1的个数
#define bitcnt(x) (__builtin_popcountll(x))


// 方格问题中的方位
int dx4[4] = {0, 0, -1, 1};
int dy4[4] = {-1, 1, 0, 0};
int dx8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};


// 常用的取模
constexpr int M1 = 1e9 + 7;
LL MOD(LL a, LL M) {
    a %= M;
    return a < 0 ? a + M : a;
}


/*
 * 数学板子
*/
// 最大公约数
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

// 快速幂
LL qmi(LL a, LL b, LL mod) {
    if (!b) return 1;
    LL tmp = qmi(a, b >> 1, mod);
    tmp = (tmp * tmp) % mod;
    if (b & 1) tmp *= a;
    return tmp % mod;
}

/*
 * 输出输出优化
 */
void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}


/*
 * 并查集函数
 * 使用的时候需要先根据打下定义好fa数组
 */
int UFfind(int f[], int a) {
    return a == f[a] ? f[a] : f[a] = UFfind(f, f[a]);
}
void UFinit(int f[], int n) {
    REP(i, 1, n) f[i] = i;
}



/******************
 * 代码开始
 * **************
 */

//#define  duipai
//#define kickstart
#define custom
// #define multiTask

/*
 * 数据初始定义
 */

int t;
int n, m;
const int N = 1e5 + 10;
int fa[N];


// 每个测试数据的方法
void solve() {
	scanf("%d%d", &n, &m);
	UFinit(fa, n);
	REP(i, 1, m) {
		char op[10];
		int a, b;
		scanf("%s %d %d", op, &a, &b);
		int ffa = UFfind(fa, a), ffb = UFfind(fa, b);
		if (op[0] == 'u') {
			fa[ffa] = ffb;
		} else {
			if (ffa == ffb) printf("YES\n");
			else printf("NO\n");
		}
	}
	
}

#ifdef custom
int main() {
    // io();

#ifdef multiTask
    scanf("%d", &t);
    while (t --)
#endif

    solve();
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


