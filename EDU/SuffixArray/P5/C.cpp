#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 4e5 + 5;

int sa[N], x[N], y[N], rk[N], cnt[N];
int height[N];
int st[N][20];

int n, m;
string s;

struct query {
	int l, r;
}qq[N];

typedef struct query QQ;

void get_sa() {

	for (int i = 1; i <= n; i ++) cnt[x[i] = s[i]] ++;
	for (int i = 2; i <= m; i ++) cnt[i] += cnt[i-1];
	for (int i = n; i; i --) sa[cnt[x[i]] --] = i;

	for (int k = 1; k < n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; i ++) y[++num] = i;
		for (int i = 1; i <= n; i ++) {
			if (sa[i] > k) {
				y[++num] = sa[i] - k;
			}
		}

		for (int i = 1; i <= m; i ++) cnt[i] = 0;
		for (int i = 1; i <= n; i ++) cnt[x[i]] ++;
		for (int i = 2; i <= m; i ++) cnt[i] += cnt[i -1];
		for (int i = n; i; i --) sa[cnt[x[y[i]]] --] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = 1, num = 1;
		for (int i = 2; i <= n; i ++) {
			x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		}
		if (num == n) break;
		m = num;
	}

	for (int i = 1; i <= n; i ++) rk[sa[i]] = i;

}

void get_st() {


	for (int i = 1; i <= n; i ++) st[i][0] = height[i];

	for (int i = 0; (1 << i) < n; i ++) {
		for (int j = 1; j + (1 << (i + 1)) - 1 <= n; j ++) {
			st[j][i + 1] = min(st[j][i], st[j + (1 << i)][i]);
		}
	}

}
int get(int l, int r) {

	int ll = log(r - l + 1) / log(2);
	return min(st[l][ll], st[r - (1 << ll) + 1][ll]);
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


auto cmp = [](const QQ &a, const QQ &b) -> bool {

    int rka = rk[a.l], rkb = rk[b.l];
    if (rka == rkb) return a.r < b.r;
    int lena = a.r - a.l + 1, lenb = b.r - b.l + 1;
    if (rka < rkb) {
        int lcp = get(rka + 1, rkb);
        if (lena == lenb) {
            if (lena <= lcp) return a.l < b.l;
            else return true;
        } else if (lena < lenb) {
            return true;
        } else {
            if (lenb > lcp) return true;
            else return false;
        }
    } else {
        int lcp = get(rkb + 1, rka);
        if (lena == lenb) {
            if (lena <= lcp) return a.l < b.l;
            else return false;
        } else if (lenb < lena) {
            return false;
        } else {
            if (lena > lcp) return false;
            else return true;
        }
    }

};


int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	memset(st, 0x3f, sizeof st);
	cin >> s;
	n = s.size();
	m = 127;
	s = ' ' + s;
	get_sa();
	get_height();
	get_st();

	int q;
	cin >> q;
	for (int i = 0; i < q; i ++) {
		int l, r;
		cin >> l >> r;
		qq[i] = {l, r};
	}
	sort(qq, qq + q, cmp);
	for (int i = 0; i < q; i ++) {
		cout << qq[i].l << ' ' << qq[i].r << '\n';
	}
	return 0;



}