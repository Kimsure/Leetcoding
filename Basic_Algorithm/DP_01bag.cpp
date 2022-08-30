/*
 * @Author: EniacKim
 * @Date: 2022-05-15 23:32:17
 * @LastEditTime: 2022-05-15 23:50:54
 * @FilePath: \AC_wing_CPP\Basic_Algorithm\DP_01bag.cpp
 * @Description: Introduction
 * @Github: https://github.com/Kimsure
 * @Email: j544899054@gmail.com
 * @Wechat: Eniac24Kim
 * @Copyright (c) 2022 by Kim, All Rights Reserved. 
 */
#include<iostream>
#include<vector>
using namespace std;

void test_1_wei_bag_problem() {
    vector<int> weight = {0, 2, 3, 4, 5};
    vector<int> value = {0, 3, 4, 5, 6};
    int bagweight = 8;

    // 二维数组
    vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

    // weight数组的大小 就是物品个数
    for(int i = 1; i < weight.size(); i++) { // 遍历物品
        for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);

        }
    }

    cout << dp[weight.size() - 1][bagweight] << endl;
}


void test_2_wei_bag_problem() {
    vector<int> weight = {2, 3, 4, 5};
    vector<int> value = {3, 4, 5, 6};
    int bagweight = 8;
    // vector<int> weight = {1, 3, 4};
    // vector<int> value = {15, 20, 30};
    // int bagweight = 4;

    // 二维数组
    vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

    // 初始化
    for (int j = weight[0]; j <= bagweight; j++) {
        dp[0][j] = value[0];
    }

    // weight数组的大小 就是物品个数
    for(int i = 1; i < weight.size(); i++) { // 遍历物品
        for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);

        }
    }

    cout << dp[weight.size() - 1][bagweight] << endl;
}

void test_3_wei_bag_problem() {
    vector<int> weight = {2, 3, 4, 5};
    vector<int> value = {3, 4, 5, 6};
    int bagweight = 8;

    // 初始化
    vector<int> dp(bagweight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // 遍历物品
        for(int j = bagweight; j >= weight[i]; j--) { // 遍历背包容量
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[bagweight] << endl;
}

int main() {
    test_1_wei_bag_problem(); // i从第0个物品开始初始化, j从0容量开始初始化("B站codereasy" 第一行 第一列都是0 )
                               // 因为是第0个 所以输入和下面的不同，要给第0个物品空出位置
    test_2_wei_bag_problem(); // i从第一个物品开始初始化, j从0容量开始初始化("代码随想录" 第一列是0，第一行不是 )
    test_3_wei_bag_problem();  // ("代码随想录" 二维DP压缩成一维DP)
}
