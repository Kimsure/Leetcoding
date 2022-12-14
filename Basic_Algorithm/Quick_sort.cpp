/*
 * @Author: EniacKim
 * @Date: 2022-04-05 22:36:31
 * @LastEditTime: 2022-04-05 23:20:29
 * @FilePath: \AC_wing_CPP\Basic_Algorithm\Quick_sort.cpp
 * @Description: Introduction
 * @Github: https://github.com/Kimsure
 * @Email: j544899054@gmail.com
 * @Wechat: Eniac24Kim
 * @Copyright (c) 2022 by Kim, All Rights Reserved. 
 */
# include <iostream>
# include <vector>

using namespace std;

const int N = 1e6+10;

int n;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r) return; // 数组里只有一个数字或者没有数字不需要排序

    int i = l - 1, j = r + 1, x = q[l + r >> 1]; // 确定左右端点，中间值(比较值)
    while (i < j)
    {
        // 根据当前值与mid的比较 两边向中间靠拢，使得最终左边都是不大于mid的，右边都是不小于mid的
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    // 第一层排好后 递归左边 递归右边
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}

class Solution {
private:
    void Qsort(vector<int>& nums, int start, int end) {
        if (start >= end) return;
        int l = start - 1, r = end + 1;
        // int mid = start + end >> 1;
        int mid = nums[start + end >> 1]; // 这里要用mid作为pivoit 是定死的 所以不能取下标 后面再取值 这样pivoit会变化 导致错误
        while (l < r) {
            do l++; while (nums[l] < mid);  // 这里大于号小于号调换一下就是升序或者降序排列
            do r--; while (nums[r] > mid);
            if (l < r) swap(nums[l], nums[r]);
        }
        Qsort(nums, start, r);
        Qsort(nums, r+1, end);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        Qsort(nums, 0, nums.size() - 1);
        return nums;
    }
};

int main() {
    scanf("%d", &n);
    for (auto i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }
    quick_sort(q, 0, n - 1);
    for (auto i = 0; i < n; i++) {
        printf("%d ", q[i]);
    }
    return 0;
}

