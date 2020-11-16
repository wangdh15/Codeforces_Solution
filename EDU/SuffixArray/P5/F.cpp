#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 4e5 + 5;

int sa1[N], rk1[N], x[N], y[N], cnt[N];
int sa2[N], rk2[N];
int height1[N], height2[N];
int rec[N];  // 记录log2的值
int n, m;
string s;
int k;
int st1[N][20], st2[N][20];
int ans;


void get_sa(int sa[]) {

    m = 'z';
    for (int i = 1; i <= m; i ++) cnt[i] = 0;
    for (int i = 1; i <= n; i ++) cnt[x[i] = s[i]] ++;
    for (int i = 2; i <= m; i ++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i --) sa[cnt[x[i]] --] = i;

    for (int k = 1; k < n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++) y[ ++num] = i;
        for (int i = 1; i <= n; i ++) {
            if (sa[i] > k) {
                y[++num] = sa[i] - k;
            }
        }
        for (int i = 1; i <= m; i ++) cnt[i] = 0;
        for (int i = 1; i <= n; i ++) cnt[x[i]] ++;
        for (int i = 2; i <= m; i ++) cnt[i] += cnt[i - 1];
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

void get_height(int sa[], int rk[], int height[]) {
    for (int i = 1; i <= n; i ++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++) {
        if (rk[i] == 1) continue;
        if (k) k --;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++;
        height[rk[i]] = k;
    }
}

void build_st(int st[][20], int height[]) {

    for (int i = 1; i <= n; i ++) st[i][0] = height[i];
    for (int i = 1; (1 << i) <= n; i ++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
            st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int query(int l, int r, int st[][20]) {
    if (l > r) swap(l, r);
    l ++;
    int t = log(r - l + 1) / log(2);
    return min(st[l][t], st[r - (1 << t) + 1][t]);
}

int work(int i, int j, int len) {
    int all_len = j - i + query(rk1[i], rk1[j], st1) + query(rk2[n - i + 2], rk2[n - j + 2], st2);
    return all_len / len;
}


int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> s;
    n = s.size();
    s = " " + s;
    get_sa(sa1);
    get_height(sa1, rk1, height1);
    build_st(st1, height1);
    reverse(s.begin() + 1, s.end());
    get_sa(sa2);
    get_height(sa2, rk2, height2);
    build_st(st2, height2);
    ans = 0;
    for (int len = 1; len <= n; len ++) {
        int last = 1;
        int i;
        for (i = len + 1; i <= n; i += len) {
            if (query(rk1[last], rk1[i], st1) >= len) continue;
            ans = max(ans, work(last, i, len));
            if (i + len - 1 <= n) last = i;
            else last = 0; 
        }
        if (last) ans = max(ans, work(last, n + 1, len));
    }
    
    printf("%d\n", ans);
    return 0;

}