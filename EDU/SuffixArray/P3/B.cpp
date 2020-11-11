#include <iostream>
using namespace std;

const int N = 1e6 + 5;

int sa[N], rk[N], x[N], y[N], cnt[N];
int height[N];

int n, m;
string s;
string p;


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

// 检查是否小于
bool check(int cur) {

    int i = sa[cur];
    int j = 0;
    while (i <= n && j < p.size()) {
        if (s[i] < p[j]) return true;
        else if (s[i] > p[j]) return false;
        else i ++, j ++;
    }
    if (n - sa[cur] + 1 < p.size()) return true;
    else return false;
}

bool check2(int cur) {

    int i = sa[cur];
    int j = 0;
    while (i <= n && j < p.size()) {
        if (s[i] < p[j]) return false;
        else if (s[i] > p[j]) return true;
        else i ++, j ++;
    }
    return false;
}


int find() {

    int l = 1, r = n;
    while( l < r) {
        int mid = l + r >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    int i = sa[l], j = 1;
    if (n - i + 1 < p.size() || s.substr(i, p.size()) != p) return 0;

    int ll = l;
    l = 1, r = n;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check2(mid)) r = mid - 1;
        else l = mid;
    }
    return l - ll + 1;

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> s;
    n = s.size();
    s = " " + s;
    get_sa();
    int q;
    cin >> q;
    while (q --) {
        cin >> p;
        cout << find() << '\n';
    }
    return 0;

}

