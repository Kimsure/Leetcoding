/*
 * @Author: EniacKim
 * @Date: 2022-04-05 23:03:39
 * @LastEditTime: 2022-04-05 23:18:20
 * @FilePath: \AC_wing_CPP\Basic_Algorithm\Merge_sort.cpp
 * @Description: Introduction
 * @Github: https://github.com/Kimsure
 * @Email: j544899054@gmail.com
 * @Wechat: Eniac24Kim
 * @Copyright (c) 2022 by Kim, All Rights Reserved. 
 */
# include <iostream>

using namespace std;

const int N = 1e6+10;

int n;
int q[N], tmp[N];
// 归并排序
void merge_sort(int q[], int l, int r)
{
    if (l >= r) return; // 数组里只有一个数字或者没有数字不需要排序

    int mid = l + r >> 1; // mid
    merge_sort(q, l, mid); // 递归左边
    merge_sort(q, mid + 1, r); // 递归右边

    int k = 0, i = l, j = mid + 1; // i是左边数组开头, j是右边数组开头
    while (i <= mid && j <= r) // 比较 把小的数先放进去(开辟了额外存放数组)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];
    // 讲比较后还未归并的剩下的数字放入到额外数组中 完成归并
    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
}

int main() {
    scanf("%d", &n);
    for (auto i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }
    merge_sort(q, 0, n - 1);
    for (auto i = 0; i < n; i++) {
        printf("%d ", q[i]);
    }
    return 0;
}

