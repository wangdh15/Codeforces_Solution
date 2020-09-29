//
// Created by wangdh on 2020/9/28.
//

#include <iostream>
using namespace std;


namespace Trie{
    const int N = 1e5 + 10;  // N需要替换为Trie图中所有可能的节点数
    int tr[N][26], cnt[N], idx = 0;

/**
 * 插入操作
 * @param s
 */
    void insert(string &s) {
        int p = 0;
        for (auto x : s) {
            if (!tr[p][x - 'a']) tr[p][x - 'a'] = ++idx;
            p = tr[p][x - 'a'];
        }
        cnt[p] ++;
    }

/**
 * 查询一个字符串出现的次数
 * @param s
 * @return
 */
    int query(string &s) {

        int p = 0;
        for (auto x : s) {
            if (!tr[p][x - 'a']) return 0;
            p = tr[p][x - 'a'];
        }
        return cnt[p];
    }


//int main() {
//    int n;
//    cin >> n;
//    while (n --) {
//        char op;
//        string x;
//        cin >> op >> x;
//        if (op == 'I') insert(x);
//        else cout << query(x) << endl;
//    }
//    return 0;
//}


/**
 * 类的实现
 */
    class Node{
    public:
        Node* ne[26];
        int cnt;
        Node() : cnt(0) {}
    };

    class Trie{
    public:
        Trie() : root(new Node()) {}
        void insert(string &s) {
            Node* cur = root;
            for (auto x : s) {
                if (!cur -> ne[x - 'a']) cur -> ne[x - 'a'] = new Node();
                cur = cur -> ne[x - 'a'];
            }
            cur -> cnt ++;
        }

        int query(string &s) {
            Node* cur = root;
            for (auto x : s) {
                if (!cur -> ne[x - 'a']) return 0;
                cur = cur -> ne[x - 'a'];
            }
            return cur -> cnt;
        }

    private:
        Node* root;
    };
}

