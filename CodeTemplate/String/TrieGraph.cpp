//
// Created by wangdh on 2020/10/7.
//

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

namespace TrieGraph {
    const int N = 1e4 + 10;

    int tr[N * 55][26], cnt[N * 26], idx;
    int ne[N * 26];

    int n, m;
    int t;

    void insert(string &s) {
        int p = 0;
        for (auto c : s) {
            if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
            p = tr[p][c - 'a'];
        }
        cnt[p] ++;
    }

    // 得到每个节点的失配指针，同时得到每个节点在26种输入的情况下跳转到的状态
    void build() {
        queue<int> qe;
        for (int i = 0; i < 26; i ++) {
            if (tr[0][i]) qe.push(tr[0][i]);
        }
        while (qe.size()) {
            int p = qe.front();
            qe.pop();
            for (int i = 0; i < 26; i ++) {
                int c = tr[p][i];
                if (!c) {
                    tr[p][i] = tr[ne[p]][i];
                } else {
                    ne[c] = tr[ne[p]][i];
                    qe.push(c);
                }
            }
        }
    }


    int match(string &s) {
        int ans = 0;
        int j = 0;
        for (auto x : s) {
            j = tr[j][x - 'a'];
            int p = j;
            while (p) {
                ans += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }
        return ans;
    }

    void solve() {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        cin >> n;
        for (int i = 0; i < n; i ++) {
            string s;
            cin >> s;
            insert(s);
        }
        build();
        string s;
        cin >> s;
        cout << match(s) << endl;
        return;
    }

    int main() {

        cin >> t;
        while (t --)
            solve();
        return 0;

    }
}



