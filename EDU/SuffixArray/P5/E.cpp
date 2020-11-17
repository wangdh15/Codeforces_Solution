#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;

const int N = 4e5 + 5;
int sa[N], rk[N], x[N], y[N], cnt[N];
int height[N];
int st[N][20];
vector<int> hs[N];
int fa[N], sz[N];

int n, m;
string s;

LL ans = 1;
int len = 1, beg = 1;

void get_sa() {
    m = 'z';

    for (int i = 1; i <= n; i ++) cnt[x[i] = s[i]] ++;
    for (int i = 2; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i --) sa[cnt[x[i]] --] = i;

    for (int k = 1; k < n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++) y[++ num] = i;
        for (int i = 1; i <= n; i ++) {
            if (sa[i] > k) {
                y[++ num] = sa[i] - k;
            }
        }
        for (int i = 1; i <= m; i ++) cnt[i] = 0;
        for (int i = 1; i <= n; i ++) cnt[x[i]] ++;
        for (int i = 2; i <= m; i ++) cnt[i] += cnt[i-1];
        for (int i = n; i; i --) sa[cnt[x[y[i]]] --] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++) {
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        }
        if (num == n) break;
        m = num;
    }

}

void get_height() {

    for (int i = 1; i <= n; i ++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++) {
        if (rk[i] == 1) continue;
        if (k) k --;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++;
        height[rk[i]] = k;
    }
}


int find(int a) {
    return a == fa[a] ? a : fa[a] = find(fa[a]);
}

void calc(int r) {
    for (auto x : hs[r]) {
        int a = find(x - 1), b = find(x);
        if ((LL) r * (sz[a] + sz[b]) > ans) {
        	ans = (LL) r * (sz[a] + sz[b]);
        	len = r;
        	beg = sa[b];
        }
        fa[a] = b;
        sz[b] += sz[a];
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	cin >> n >> m;
	s = " ";
    for (int i = 1; i <= n; i ++) {
    	int x;
    	cin >> x;
    	char a = 'a' + x;
    	s += a;
    }
    m = 'z';
    get_sa();
    get_height();
    for (int i = 1; i <= n; i ++) fa[i] = i, sz[i] = 1;
    for (int i = 2; i <= n; i ++) hs[height[i]].push_back(i);
    for (int i = n - 1; i >= 1; i --) calc(i);
    if (ans < n) {
    	ans = n;
    	beg = 1;
    	len = n;
    }
    cout << ans << '\n';
    cout << len << '\n';
	for (int i = 0; i < len; i ++) cout << s[beg + i] - 'a' << ' ';
    return 0;
}