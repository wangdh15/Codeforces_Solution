//
// Created by wangdh on 2020/10/7.
//

#include <string>
#include <iostream>
#include <queue>
using namespace std;

namespace AC{
    const int N = 1e4 + 10;

    int tr[N * 55][26], cnt[N * 26], idx;
    int ne[N * 26];   // 存储每个节点的失配指针，也就是失配之后跳转到的节点的下标

    int n, m;
    int t;

    void insert(string &s) {  // 构建Trie图
        int p = 0;
        for (auto c : s) {
            if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
            p = tr[p][c - 'a'];
        }
        cnt[p] ++;
    }


    void build() {
        /**
         * 使用广度优先遍历的思想来计算每个节点的失配指针
         */
        queue<int> qe;
        for (int i = 0; i < 26; i ++) {  // 长度为1的节点失配为零
            if (tr[0][i]) qe.push(tr[0][i]);
        }
        while (qe.size()) {
            int p = qe.front();
            qe.pop();
            for (int i = 0; i < 26; i ++) {
                int c = tr[p][i];
                if (!c) continue;
                int j = ne[p];
                while (j && !tr[j][i]) j = ne[j];   // 尝试跳转到前面的最长公共前缀的部分进行匹配
                if (tr[j][i]) j = tr[j][i];
                ne[c] = j;
                qe.push(c);    // 将Trie中的节点加入到队列中
            }
        }
    }


    int match(string &s) {
        int ans = 0;
        int j = 0;
        for (auto x : s) {
            while (j && !tr[j][x - 'a']) j = ne[j];
            if (tr[j][x - 'a']) j = tr[j][x - 'a'];
            int p = j;
            while (p) {  // 到达一个节点之后就需要统计一下当前节点代表的字符串的后缀中是不是有字典中的词
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

