//
// Created by wangdh on 2020/9/28.
//


/*
 * 二分的写法：
 * 1. 确定q[mid]和target相等的时候将l, r哪一个移动到mid上
 * 2. 根据1的更新公式，选择mid的更新公式
 * 3. 根据2得到的mid的更新公式，对l, r进行扩，如果mid选择左中点，则扩r；如果mid选择右中点，则扩l(保证所有点都被判断到)
 */

/**
 * 找到数组q中第一个不小于target的位置
 * @param q 输入的数组
 * @param n 数组的长度
 * @param target 目标元素
 * @return
 */
int binary_search(int q[], int n, int target) {

    int l = 0, r = n;  // 因为选择的是靠左的mid，所以右边界向后扩一位
    while (l < r) {
        int mid = l + r >> 1;
        if (q[mid] < target) l = mid + 1;
        else r = mid;
    }
    return l;

}

/**
 * 找到数组中最后一个不大于target的位置
 * @param q
 * @param n
 * @param target
 * @return
 */
int binary_search2(int q[], int n, int target) {
    int l = -1, r = n - 1;
    while (l > r) {
        int mid = l + r + 1 >> 1;
        if (q[mid] <= target) l = mid;
        else r = mid - 1;
    }
    return l;  // 如果l返回-1，则说明数组中的元素都大于target

}
