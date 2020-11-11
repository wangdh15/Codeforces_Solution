/**
 
 https://www.acwing.com/problem/content/2717/
 
 后缀数组。能够同时求得两个数组
 1. sa[i] 表示排第i位的后缀编号
 2. height[i] 表示sa[i]和sa[i-1]这两个后缀的最长公共前缀
 在height数组上建立维护区间最小值的数据结构，如线段树或者ST表，就可以查询任意两个后缀的最长公共前缀长度
 
 
 */

#include <iostream>
using namespace std;

const int N = 1e6 + 5;

int sa[N], rk[N], x[N], y[N], cnt[N];
int height[N];

int n, m;
string s;


void get_sa() {
    
    m = 'z';
    for (int i = 1; i <= n; i ++) cnt[x[i] = s[i]] ++;
    for (int i = 2; i <= m; i ++) cnt[i] += cnt[i - 1];
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
        for (int i = 2; i <= m; i ++) cnt[i] += cnt[i - 1];
        
        for (int i = n; i; i --) sa[cnt[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++) {
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        }
        if (num == n) break;
        m = num;
    }
    for (int i = 1; i <= n; i ++) rk[sa[i]] = i;
}

void get_height() {
    
    int k = 0;
    for (int i = 1; i <= n; i ++) {
        if (rk[i] == 1) continue;
        if (k) k --;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++;
        height[rk[i]] = k;
    }
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s;
    n = s.size();
    s = " " + s;
    
    get_sa();
    get_height();
    for (int i = 1; i <= n; i ++) cout << sa[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i ++) cout << height[i] << ' ';
    return 0;
}
