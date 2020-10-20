//
// Created by wangdh on 2020/10/20.
//

#include <iostream>
#include <functional>
using namespace std;

namespace Heap {
        constexpr int N = 1e5 + 10;
        int q[N];
        int n, m;
        int cnt;

        /**
         * 调整算法
         * @param u 下标
         * @param f lambda表达式，
         */
        void down(int u, std::function<bool (int, int)> const &f) {
            int t = u;
            if (u * 2 <= cnt && f(q[u * 2], q[u])) t = u * 2;
            if (u *2 + 1 <= cnt && f(q[u * 2 + 1], q[t])) t = u * 2 + 1;
            if (u != t) {
                swap(q[u], q[t]);
                down(t, f);
            }
        }

        int main() {
            cin >> n >> m;
            cnt = n;
            for (int i = 1; i <= n; i ++) cin >> q[i];
            std::function<bool (int, int)> f = [](int i, int j) -> bool {return i < j;};
            for (int i = n / 2; i > 0; i --) down(i, less<int>());  // 构造堆
            while (m --) {
                cout << q[1] << " ";
                swap(q[1], q[cnt]);
                cnt --;
                down(1, less<int>());
            }
            return 0;
        }
}

namespace HeapSupportModifyDelete {

    constexpr int N = 1e5 + 10;
    int h[N];

    // l2h[i]表示第i个插入的数当前在h数组中的位置
    // h2l[i]表示h数组中的第i个数是第几个插入的
    int l2h[N], h2l[N];

    int n;
    int cnt = 0;  // 记录当前堆中有多少元素
    int idx = 0; // 记录数据插入的序号


    // 交换当前h数组中的a位置的元素和b位置的元素
    // 维护三个数组的值
    void heap_swap(int a, int b) {
        int la = h2l[a], lb = h2l[b];
        l2h[la] = b;
        l2h[lb] = a;
        h2l[a] = lb;
        h2l[b] = la;
        swap(h[a], h[b]);
    }

    // 向下更新的操作
    void down(int u) {
        int t = u;
        if (u * 2 <= cnt && h[u * 2] < h[t]) t = u * 2;
        if (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
        if (t != u) {
            heap_swap(u, t);
            down(t);
        }
    }

    // 向上更新的操作
    void up(int u) {
        while (u / 2 && h[u / 2] > h[u]) {
            heap_swap(u, u / 2);
            u = u / 2;
        }
        return;
    }

    int main() {
        cin >> n;
        while (n --) {
            string op;
            cin >> op;
            if (op == "I") {
                int x;
                cin >> x;
                cnt++;
                idx ++;
                l2h[idx] = cnt;
                h2l[cnt] = idx;
                h[cnt] = x;
                up(cnt);
            } else if (op == "PM") {
                cout << h[1] << endl;
            } else if (op == "DM") {
                heap_swap(1, cnt);
                cnt --;
                down(1);
            } else if (op == "D") {
                int k;
                cin >> k;
                int ii = l2h[k];
                heap_swap(ii, cnt);
                cnt --;
                up(ii);
                down(ii);
            } else {
                int k, x;
                cin >> k >> x;
                int ii = l2h[k];
                h[ii] = x;
                up(ii);
                down(ii);
            }
        }
        return 0;
    }
}
