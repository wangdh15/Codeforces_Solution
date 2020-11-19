#include <iostream>
#include <cstdio>


using namespace std;
const int maxn = 1e6 + 10;
typedef long long ll;

struct SA
{
    char s[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn], n;

    void build_sa(int n, int m)
    {
        int *x = t, *y = t2;
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) c[x[i] = s[i]]++;
        for(int i = 1; i < m; i++) c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(int i = n - k; i < n; i++) y[p++] = i;
            for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(int i = 0; i < m; i++) c[i] = 0;
            for(int i = 0; i < n; i++) c[x[y[i]]]++;
            for(int i = 0; i < m; i++) c[i] += c[i - 1];
            for(int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for(int i = 1; i < n; i++)
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    int rk[maxn], height[maxn];

    void getHeight()
    {
        for(int i = 1; i <= n; i++) rk[sa[i]] = i;
        for(int i = 0, k = 0; i < n; i++)
        {
            if(k) k--;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) k++;
            height[rk[i]] = k;
        }
        for(int i = n; i > 0; i --) rk[i] = rk[i - 1];
    }

    int dp[maxn][21];

    void RMQ()
    {
        for(int i = 1; i <= n; i ++) dp[i][0] = height[i];
        for(int j = 1; (1 << j) < maxn; j ++)
            for(int i = 1; i + (1 << j) - 1 <= n; i ++)
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r)
    {
        int k = 0;
        while((1 << (k + 1)) <= r - l + 1) k ++;
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }

    int lcp(int x, int y)
    {
        x = rk[x], y = rk[y];
        if(x > y) swap(x, y);
        return query(x + 1, y);
    }
}A, B;

int n, k;
int ans1 = 1, ans2 = 1;

void work(int l, int r, int p)
{
    int exR = A.lcp(l, r + 1), exL = B.lcp(n + 1 - r, n + 1 - l + 1);
    l -= exL, r += exR;
	if ((double)(r - l + 1) / p > (double)ans1 / ans2) {
		ans1 = r - l + 1;
		ans2 = p;
	}
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main()
{
    int _;
    scanf("%d", &_);
    while(_ --)
    {
        scanf("%s", A.s);
        n = strlen(A.s);
        reverse_copy(A.s, A.s + n, B.s); A.n = B.n = n;
        A.build_sa(n + 1, 130), B.build_sa(n + 1, 130);
        A.getHeight(), B.getHeight();
        A.RMQ(), B.RMQ();
        
        for(int i = 1; i <= n; i ++)
        {
            int last = 1;
            for(int j = i + 1; j <= n; j += i)
            {
                if(A.lcp(last, j) >= i) continue;
                work(last, j - 1, i);
                if(j + i - 1 <= n) last = j;
                else last = 0;
            }
            if(last) work(last, n, i);
        }
        int _gcd = gcd(ans1, ans2);
        
        printf("%ld/%d\n", ans1 / _gcd, ans2 / _gcd);
    }
    return 0;
}