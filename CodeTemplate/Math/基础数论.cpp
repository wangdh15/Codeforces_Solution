#include <iostream>
#include <vector>

using namespace std;

/**
 * 1. 线性筛法: https://www.acwing.com/problem/content/870/
 * 2. 分解质因数: https://www.acwing.com/problem/content/869/
 * 3. 快速幂:
 */

class BasicNumberTheory{
public:

    /**
     * 线性筛法筛素数
     * 得到小于等于n的所有素数，时间复杂度为O(n)
     * @param n ： 范围
     * @return 包含素数的vector
     */
    static vector<int> get_primes(int n) {
        vector<int> ps;
        vector<bool> st(n + 1);
        for (int i = 2; i <= n; i ++) {
            if (!st[i]) ps.push_back(i);
            for (int j = 0; ps[j] <= n / i; j ++) {
                st[ps[j] * i] = true;
                if (i %  ps[j] == 0) break;
            }
        }
        return ps;
    }

    /**
     * 对n进行素因子分解
     * @param n 输入
     * @return vector<pair<int, int>> 每个pair第一个数素数，第二个是指数
     */
    static vector<pair<int, int>> PrimeFactorization(int n) {
        vector<pair<int, int>> ans;
        for (int i = 2; i <= n / i; i ++) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) cnt ++, n /= i;
                ans.push_back({i, cnt});
            }
            if (n == 1) break;
        }
        if (n > 1) ans.push_back({n, 1});
        return ans;
    }

};

