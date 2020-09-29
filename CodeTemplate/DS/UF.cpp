//
// Created by wangdh on 2020/9/28.
//


// 类的方法
class UF{
public:
    UF(int _cap) : cap(_cap) , f(new int[_cap]), cnt(new int[_cap]) {
        for (int i = 1; i < _cap; i ++) {
            f[i] = i;
            cnt[i] = 1;
        }
    }

    // 返回a的根
    int find(int a) {return a == f[a] ? f[a] : f[a] = find(f[a]);}

    // 将a和b所属的联通分量合并
    void uinon(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            f[fa] = fb;
            cnt[fb] += cnt[fa];
        }
    }
    // 返回a所属的联通分量中的节点数
    int nodes(int a) {return cnt[find(a)];}

private:
    int cap;   // 容量
    int *f;  // 父节点数组
    int *cnt;  // 保存每个联通分量的节点数

};

