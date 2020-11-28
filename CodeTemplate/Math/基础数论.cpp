#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 1. 线性筛法: https://www.acwing.com/problem/content/870/
 * 2. 分解质因数: https://www.acwing.com/problem/content/869/
 * 3. 求所有素数: https://www.acwing.com/problem/content/871/
 * 4. 约数个数公式: (1 + a1) * (1 + a2) * (1 + a3)... * (1 + ai)
 * 5. 约数之和：对约数个数公式进行扩展。
 * 6. 欧几里得算法求最大公约数： https://www.acwing.com/problem/content/874/
 * 3. 快速幂: https://www.acwing.com/problem/content/877/
 */

class BasicNumberTheory{
public:
    
    typedef long long LL;
    
    /**
     * 线性筛法筛素数
     * 得到小于等于n的所有素数，时间复杂度为O(n)
     * @param n ： 范围
     * @return 包含素数的vector
     */
    static vector<int> getPrimes(int n) {
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
    static vector<pair<int, int>> primeFactorization(int n) {
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
    
    /**
     * 求n的所有因数
     * @param n
     * @return
     */
    static vector<int> getFactor(int n) {
        vector<int> ans;
        for (int i = 1; i <= n / i; i ++) {
            if (n % i == 0) {
                ans.push_back(i);
                if (n / i != i) ans.push_back(n / i);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
    
    /**
     * 得到n的所有的约数之和
     * @param n
     * @param mod 为了避免过大，取模
     * @return
     */
    static int getFactorSum(int n, int mod) {
        
        auto ans = BasicNumberTheory::primeFactorization(n);
        int res = 1;
        for (auto x : ans) {
            int p = x.first, cnt = x.second;
            int t = 1;
            while (cnt --) t = (t * p + 1) % mod;
            res = (res * t) % mod;
        }
        return res;
    }
    
    /**
     * 欧几里得算法求最大公约数
     * @param a
     * @param b
     * @return
     */
    static int getGCD(int a, int b) {
        if (!b) return a;
        return BasicNumberTheory::getGCD(b, a % b);
    }
    
    /**
     * 快速幂算法，递归版本
     * @param a
     * @param b
     * @param mod
     * @return
     */
    static LL qmi(LL a, LL b, LL mod) {
        if (!b) return 1;
        LL res = qmi(a, b >> 1, mod);
        res = (res * res) % mod;
        if (b & 1) res = (res * a) % mod;
        return res;
    }
    
    /**
     * 快速幂算法，迭代版本
     * @param a
     * @param b
     * @param mod
     * @return
     */
    static LL qmi2(LL a, LL b, LL mod) {
        LL res = 1;
        LL t = 1;
        while (b) {
            if (b & 1) res = (res * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return res;
    }
    
    
};

int main() {
    int a;
    cin >> a;
    cout << BasicNumberTheory::getFactorSum(a, 1e9 + 7);
    return 0;
}

