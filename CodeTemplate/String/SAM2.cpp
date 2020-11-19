/**
 * 后缀自动机模板, 类实现
 * https://www.acwing.com/problem/content/2768/
 */

#include <iostream>
#include <vector>
using namespace std;

const int ALPHA_SIZE = 26; // 字符集大小

class Node {
public:
    int len, fail;  // 存储当前状态代表的最长子串的长度，faile指针
    int ch[ALPHA_SIZE]; // 存储孩子指针
    int num; // 存储当前节点代表的字符串在原始字符串中出现的次数
};

class SAM {
public:
    
    typedef unsigned long long ULL;
    
    SAM(string &s) : tr(vector<Node>(MAX_LEN << 1)),
    st(vector<bool>(MAX_LEN << 1)),
    idx(1),
    last(1),
    h(vector<int>(MAX_LEN << 1, -1)),
    e(vector<int>(MAX_LEN << 1)),
    ne(vector<int>(MAX_LEN << 1)),
    g_idx(0) {
        for (auto x : s) {
            _extend(x - 'a');
        }
    }
    
    //求本质不同的子串的数量
    ULL getSubstringNum() {
        return _dfs(1);
    }
    
    // 跑完之后，可以求出每个状态代表的子串出现的次数，
    // 一个状态代表的所有子串在原串中出现的次数是相同的
    ULL getNumForEverySubString() {
        _build_tree();
        _dfs2(1);
    }
    
    // 得到一个子串长度和其出现次数乘积的最大值，其中子串出现次数要大于1
    ULL getMaxLengthTimesOccurTime() {
        getNumForEverySubString();
        ULL ans = 0;
        for (int i = 1; i <= idx; i ++) {
            if (tr[i].num == 1) continue;
            ans = max(ans, (ULL)(tr[i].len) * tr[i].num);
        }
        return ans;
    }
    
private:
    
    static const int MAX_LEN = 1e6 + 5;
    
    vector<Node> tr;
    int idx, last;  // 表明当前用到了哪个点，以及上一个代表字符串末尾的状态的位置
    vector<bool> st;  // 用于dfs时判断是否遍历到了
    vector<int> h, e, ne;  // 用于在fail指针上建反边从而得到一棵树
    int g_idx;
    
    // 增量的方式构造SAM
    void _extend(int c) {
        
        int p = last, np = last = ++idx;
        tr[np].len = tr[p].len + 1;
        tr[np].num = 1;
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
                tr[nq].num = 0;  // 不能把num也给复制了，新开的num要为零
                tr[q].fail = nq;  // 维护faile指针
                tr[np].fail = nq;
                tr[nq].len = tr[p].len + 1;  // 新创建的节点，且强制让他代表新加入的字符扩展得到的字传的长度
                // 将前面到q的边都转移到nq
                while (p && tr[p].ch[c] == q) tr[p].ch[c] = nq, p = tr[p].fail;
            }
        }
    }
    
    // 求本质不同的字符串的个数
    ULL _dfs(int cur) {
        ULL ans = tr[cur].len - tr[tr[cur].fail].len;
        st[cur] = true;
        for (int i = 0; i < ALPHA_SIZE; i ++) {
            int t = tr[cur].ch[i];
            if (t && !st[t]) ans += _dfs(t);
        }
        return ans;
    }
    
    void _add(int a, int b) {
        e[g_idx] = b, ne[g_idx] = h[a], h[a] = g_idx ++;
    }
    
    // 建反向树
    void _build_tree() {
        for (int i = 2; i <= idx; i ++) _add(tr[i].fail, i);
    }
    
    // 用于求每个节点代表的字符串出现的次数
    void _dfs2(int cur) {
        for (int i = h[cur]; ~i; i = ne[i]) {
            int node = e[i];
            _dfs2(node);
            tr[cur].num += tr[node].num;
        }
    }
};

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    cin >> s;
    SAM sam(s);
    cout << sam.getMaxLengthTimesOccurTime();
    return 0;
    
}
