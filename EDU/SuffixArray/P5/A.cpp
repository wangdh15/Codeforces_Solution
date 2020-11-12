#include <iostream>
using namespace std;

const int N = 4e5 + 5;

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
	unsigned long long ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans += n - sa[i] + 1 - height[i];
	}
	cout << ans;
    return 0;
}