/**
 * Treap = Tree + Heap,同时满足二叉搜索树和堆的性质
 *
 * https://www.luogu.com.cn/problem/P3369
 *
 */

#include <iostream>
using namespace std;

constexpr int N = 1e5 + 10;

class Treap {
public:
    
    static constexpr int INF = 1e9;
    
    explicit Treap(int max_node_cnt):
    idx(3),
    data(new Node[max_node_cnt]) {
        data[1].init(-INF);
        data[2].init(INF);
        root = 1;
        data[1].rc = 2;
        pushup(root);
        if (data[1].val < data[2].val) zag(root);
    }
    ~Treap() {delete []data;}
    
    void insert(int key) {_insert(root, key);}
    void erase(int key) {_erase(root, key);}
    int get_rank_by_key(int key) {return _get_rank_by_key(root, key) - 1;}
    int get_key_by_rank(int rank) {return _get_key_by_rank(root, rank + 1);}
    int get_prev(int key) {return _get_prev(root, key);}
    int get_next(int key) {return _get_next(root, key);}
    
    
private:
    
    class Node {
    public:
        int lc, rc; // 记录左孩子， 右孩子还有父节点
        int key, val;  // 记录当前节点用于平衡树的key，和用于堆的随机生成的val
        int cnt, size;  // 记录当前节点为根的子树的size和当前key的个数cnt
        void init(int _key) { // 初始化方法
            key = _key;
            cnt = size = 1;
            lc = rc = 0;
            val = rand();
        }
    };
    
    Node *data; // 指向申请的节点数组
    int root;   // 记录根节点的编号
    int idx; // 记录当前用到了哪个节点
    
    
    // 利用孩子节点的size信息来更新自己的size信息
    void pushup(int q) {
        data[q].size = data[data[q].lc].size + data[data[q].rc].size + data[q].cnt;
    }
    
    // 右旋算法
    void zig(int &p) {
        int q = data[p].lc;
        data[p].lc = data[q].rc;
        data[q].rc = p;
        pushup(p);
        pushup(q);
        p = q;
    }
    
    // 左旋算法
    void zag(int &p) {
        int q = data[p].rc;
        data[p].rc = data[q].lc;
        data[q].lc = p;
        pushup(p);
        pushup(q);
        p = q;
    }
    
    // 插入操作
    void _insert(int &p, int key) {
        
        if (!p) {
            p = idx ++;
            data[p].init(key);
        } else {
            if (data[p].key == key) data[p].cnt ++;
            else if (data[p].key > key) {
                _insert(data[p].lc, key);
                if (data[p].val < data[data[p].lc].val) zig(p);
            }
            else {
                _insert(data[p].rc, key);
                if (data[p].val < data[data[p].rc].val) zag(p);
            }
        }
        pushup(p);
    }
    
    // 删除操作
    void _erase(int &p, int key) {
        
        if (!p) return;
        else if (data[p].key == key) {
            if (data[p].cnt > 1) data[p].cnt --;
            else if (!data[p].lc && !data[p].rc) p = 0;
            else {
                if (!data[p].rc || data[data[p].lc].val > data[data[p].rc].val) {  // 这个地方注意，利用了rand()的值大于零的性质
                    zig(p);
                    _erase(data[p].rc, key);
                } else {
                    zag(p);
                    _erase(data[p].lc, key);
                }
            }
        } else if (data[p].key < key) _erase(data[p].rc, key);
        else _erase(data[p].lc, key);
        pushup(p);
    }
    
    // 通过值找排名
    int _get_rank_by_key(int p, int key) {
        if (data[p].key == key) return data[data[p].lc].size + 1;
        else if (data[p].key < key) return _get_rank_by_key(data[p].rc, key) + data[data[p].lc].size + data[p].cnt;
        else return _get_rank_by_key(data[p].lc, key);
    }
    
    // 通过排名找值
    int _get_key_by_rank(int p, int rank) {
        
        if (data[data[p].lc].size >= rank) return _get_key_by_rank(data[p].lc, rank);
        else if (data[data[p].lc].size + data[p].cnt < rank) return _get_key_by_rank(data[p].rc, rank - data[data[p].lc].size - data[p].cnt);
        else return data[p].key;
        
    }
    
    // 得到前驱
    int _get_prev(int p, int key) {
        if (!p) return -INF;
        if (data[p].key < key) return max(data[p].key, _get_prev(data[p].rc, key));
        else return _get_prev(data[p].lc, key);
    }
    
    // 得到后继
    int _get_next(int p, int key) {
        if (!p) return INF;
        if (data[p].key > key) return min(data[p].key, _get_next(data[p].lc, key));
        else return _get_next(data[p].rc, key);
    }
};

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    cin >> n;
    Treap treap(N);
    
    while (n --) {
        int op, x;
        cin >> op >> x;
        if (op == 1) treap.insert(x);
        else if (op == 2) treap.erase(x);
        else if (op == 3) cout << treap.get_rank_by_key(x) << '\n';
        else if (op == 4) cout << treap.get_key_by_rank(x) << '\n';
        else if (op == 5) cout << treap.get_prev(x) << '\n';
        else cout <<  treap.get_next(x) << '\n';
    }
    return 0;
}

