/**
 *
 * 后缀数组模板，较为工程化的实现
 * https://www.luogu.com.cn/problem/P3809
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SuffixArray{

public:

    SuffixArray(const string &str) :
    str_length(str.size()),
    sa(vector<int>(str_length + 1)),
    rk(vector<int>(str_length + 1)),
    cur_keys(vector<int>(str_length + 1)),
    sort_result_by_second_key(vector<int>(str_length + 1)),
    cnt(vector<int>(max(256u, str_length + 1))) {
        _get_sa(str);
    }

    ~SuffixArray() = default;

    vector<int> get_sa() const {return sa;}

    vector<int> get_rk() const {return rk;}


private:
    uint32_t str_length;
    vector<int> sa, rk;  // sa存储后缀数组，rk存储排序数组，两者是互逆关系
    vector<int> cur_keys; // 存储第i个后缀当前离散化的key
    vector<int> sort_result_by_second_key; // 存储按照第二个key排序的结果，第i个元素表示排在第i位的后缀的标号
    vector<int> cnt; // 计数数组，用于基数排序

    void _get_sa(const string &s) {

        // 按照一个字母初始化好sa数组和关键字数组
        uint32_t discrete_key_nums = 255;
        for (int i = 1; i <= str_length; i ++) {
            cur_keys[i] = s[i - 1];
            cnt[cur_keys[i]]++;
        }
        for (int i = 2; i <= discrete_key_nums; i ++) cnt[i] += cnt[i - 1];
        // 基数排序，逆着遍历保证稳定
        for (int i = str_length; i; i --) {
            sa[cnt[cur_keys[i]]] = i;
            cnt[cur_keys[i]] --;
        }

        // 开始倍增处理
        for (int cur_len = 1; cur_len < str_length; cur_len <<= 1) {

            // 按照第二个关键字进行排序
            int idx = 0;
            // 第二关键字为零的先处理好
            for (int i = str_length - cur_len + 1; i <= str_length; i ++) sort_result_by_second_key[++ idx] = i;
            // 下表为i的关键字为下表为i - cur_len的第二个关键字，由于已经有序了，所以直接扫描即可
            for (int i = 1; i <= str_length; i ++)
                if (sa[i] > cur_len)
                    sort_result_by_second_key[++ idx] = sa[i] - cur_len;

            // 开始按照第一个关键字进行排序
            for (int i = 1; i <= discrete_key_nums; i ++) cnt[i] = 0;
            for (int i = 1; i <= str_length; i ++) cnt[cur_keys[i]] ++;
            for (int i = 2; i <= discrete_key_nums; i ++) cnt[i] += cnt[i - 1];

            // 逆序扫描，确保第一个关键字相同的情况下，能够正确按照第二个关键字的顺序排序
            for (int i = str_length; i; i --) sa[cnt[cur_keys[sort_result_by_second_key[i]]] --] = sort_result_by_second_key[i], sort_result_by_second_key[i] = 0;

            // 交换关键字数组和第二个关键字排序结果数组，
            // 因为要重新计算cur_keys，而且第二个关键字排序结果没有用了
            // 要用上一步的cur_keys来计算新的keys，且不能覆盖，所以就用第二个关键字排序数组
            // 之后这两个数组的身份也发生了变化
            swap(cur_keys, sort_result_by_second_key);

            // 计算新长度的第一关键字
            // 进行离散化
            cur_keys[sa[1]] = 1, discrete_key_nums = 1;
            for (int i = 2; i <= str_length; i ++) {
                if (sort_result_by_second_key[sa[i]] == sort_result_by_second_key[sa[i - 1]] && sort_result_by_second_key[sa[i] + cur_len] == sort_result_by_second_key[sa[i - 1] + cur_len])
                    cur_keys[sa[i]] = discrete_key_nums;
                else
                    cur_keys[sa[i]] = ++ discrete_key_nums;
            }
            // 不同的关键字个数已经和字符串长度相同
            // 说明已经将所有的后缀分开，
            // 不需要再继续下去
            if (discrete_key_nums == str_length) break;
        }
        // 根据求的sa数组，直接求rk数组
        for (int i = 1; i <= str_length; i ++) rk[sa[i]] = i;
    }

};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    SuffixArray suffixArray(s);
    vector<int> res=  suffixArray.get_sa();
    // cout << s.size() << ' ';
    for (int i = 1; i <= s.size(); i ++) cout << res[i] << ' ';
    return 0;
}
