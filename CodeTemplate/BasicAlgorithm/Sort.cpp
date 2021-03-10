//
// Created by wangdh on 2020/9/28.
//
#include <iostream>
using namespace std;

/**
 * 快排模板，这里的每一个变量，每个符号都不能随意改变。
 * @param q
 * @param l  闭区间的左端点
 * @param r  闭区间的右端点
 */
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do i ++; while (q[i] < x);
        do j --; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

/**
 * 归并排序
 * @param q 要排序的数组
 * @param tmp 用于归并的临时数组
 * @param l 闭区间左端点
 * @param r 闭区间右端点
 */
void merge_sort(int q[], int tmp[], int l, int r) {

    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(q, tmp, l, mid);
    merge_sort(q, tmp, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (q[i] < q[j]) {
            tmp[k ++] = q[i ++];
        } else {
            tmp[k ++] = q[j ++];
        }
    }
    while (i <= mid) tmp[k ++] = q[i ++];
    while (j <= r)  tmp[k ++] = q[j ++];
    for (int i = l, k = 0; i <= r; i ++, k ++) q[i] = tmp[k];
    return;
}

