/**
 *
 * 后缀自动机模板
 * https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/A
 *
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class SAM {
public:

    typedef unsigned long long ULL;

    SAM(string &s) : tr(vector<Node>(MAX_LEN << 1)),
    st(vector<bool>(MAX_LEN)),
    idx(1),
    last(1) {
        for (auto x : s) {
            _extend(x - 'a');
        }
    }

    ULL getSubstringNum() {

        return _dfs(1);
    }


private:

    static const int MAX_LEN = 1e6 + 5;

    class Node {
    public:
        int len, fail;
        int ch[26];
    };

    vector<Node> tr;
    int idx, last;
    vector<bool> st;

    // 增量的方式构造SAM
    void _extend(int c) {

        int p = last, np = last = ++idx;
        tr[np].len = tr[p].len + 1;
        // 沿着faile指针向前不断扩充新增加的子串，
        // 如果发现状态没有在状态机中则练一个到最后的状态的Trie边
        while (p && !tr[p].ch[c]) tr[p].ch[c] = np, p = tr[p].fail;
        // p 为零，说明所有的都只能通过新增的方式来做
        if (!p) tr[np].fail = 1;
            // 发现某个状态在扩充的时候扩充到了状态机已经存的的一个状态
        else {
            int q = tr[p].ch[c];
            if (tr[q].len == tr[p].len + 1) tr[np].fail = q; // 如果这个状态代表的最大长度刚好是新增加的，则直接将末尾的fa指针指向它即可。
            else {  // 否则的话，需要分裂节点
                int nq = ++ idx;
                tr[nq] = tr[q];
                tr[q].fail = nq;  // 维护faile指针
                tr[np].fail = nq;
                tr[nq].len = tr[p].len + 1;  // 新创建的节点，且强制让他代表新加入的字符扩展得到的字传的长度
                // 将前面到q的边都转移到nq
                while (p && tr[p].ch[c] == q) tr[p].ch[c] = nq, p = tr[p].fail;
            }
        }
    }

    ULL _dfs(int cur) {
        ULL ans = tr[cur].len - tr[tr[cur].fail].len;
        st[cur] = true;
        for (int i = 0; i < 26; i ++) {
            int t = tr[cur].ch[i];
            if (t && !st[t]) ans += _dfs(t);
        }
        return ans;
    }


};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    SAM sam(s);
    cout << sam.getSubstringNum();
    return 0;

}


