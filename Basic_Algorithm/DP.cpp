/*
 * @Author: EniacKim
 * @Date: 2022-06-06 17:03:39
 * @LastEditTime: 2022-06-06 17:03:39
 * @FilePath: \AC_wing_CPP\Basic_Algorithm\DP.cpp
 * @Description: Introduction
 * @Github: https://github.com/Kimsure
 * @Email: j544899054@gmail.com
 * @Wechat: Eniac24Kim
 * @Copyright (c) 2022 by Kim, All Rights Reserved. 
 */

/*
 * 几个模板里注意的点:
 * 0. 背包问题的转化思路, 一般看到当某某属性最大时需要算得什么什么, 此时该属性为背包容量，与之相对的属性为物品。
 * 1. 01背包和完全背包的区别: 01背包外层正序内层倒序，完全背包两层都是正序
 * 2. 注意因为递推公式导致的循环初始值设定: 当递推出现dp[j - coins[i]] + m, 要保证 j - coins[i] >= 0, 所以内层循环的初始值为coins[i]而不是0
 *    注意这种总结的情况目前只分析完全背包问题
 *    注意此情况一般出现在循环外层物品内层背包时. 当外层背包内层物品时, 一般会使用if 来判断是否递推 此时可不考虑循环初始值问题
 * 2_1. 01背包中的一维DP 内层循环必须是倒序, 那么就是根据递推公式里'j - weight[i]'来确定内层循环的范围
 * 3. 注意排列组合的循环不同: 外层for循环遍历物品,内层for遍历背包得到组合数(不要求顺序), 相反的遍历得到排列数(要求排序)
 * 4. 不同题目的递推公式: 1) 组合问题: dp[i] += dp[i-num]; 2)布尔值问题: dp[i] = dp[i] or dp[i-num]; 
 *                      3) 最大最小问题: dp[i] = min(dp[i], dp[i-num] + m)或者dp[i] = max(dp[i], dp[i-num] + m) 
 * (其中m可能是数值也可能是物品value[i] or 物品weight[i]，前者是一般的重量和价值不同，后者是物品质量和价值等价)
 */

/*
 * 动态规划的五部曲
 * 1. 确定DP数组的下标与含义，
 * 2. 确定递推公式：如斐波那契数列dp[i] = dp[i - 1] + dp[i - 2]
 * 3. 初始化DP数组，如斐波那契数列dp[0] = 0, dp[1] = 1
 * 4. 确定遍历顺序，一维还是二维，从前往后还是从后往前
 * 5. 举例推DP数组
 */
# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>

using namespace std;

/*
 * 斐波那契数列
 */
class Solution1 {
   public:
        Solution1() {
            cout << "Fiber list object created" << endl;
        }
        int fib(int N) {
            if (N <= 1) return N;
            vector<int> dp(N + 1);
            dp[0] = 0;
            dp[1] = 1;
            for (int i = 2; i <= N; i++) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            return dp[N];
        };
};

/*
 * 爬楼梯，(可能1次爬两层也可能1次爬三层)
 */
class Solution2 {
    public:
        Solution2() {
            cout << "Claim stairs object created" << endl;
        }
        int floors(int a) {
            int N = 100000;
            vector<int> dp(N + 1); // 爬到第i层所需要的次数
            dp[1] = 1; // 到第一层是1次
            dp[2] = 2; // 到第二次是2次，(0->2, 1->2)
            for (int i = 3; i <= a; ++i) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            return dp[a];
        }
};

/*
 * 爬楼梯进阶版 (可能1次爬两层,也可能1次爬三层,也可能1次爬四层,也可能1次爬五层,...,也可能1次爬 m 层)
 * 这种情况就是完全背包问题: 爬1层楼梯, 2 3 4...m 层楼梯时物品, 楼顶所需楼梯层数就是背包容量, 爬多少层可以重复利用(可以爬多次一层)
 * 这样就是完全背包的思路了, 问跳到楼顶有几种方法其实就是问装满背包有几种方法。是背包里求排列问题
 * 五部曲:
 * 1. dp[j]代表到a层共有多少种方式; 2. 初始化dp[0] = 1 不好解释 为了递推; 4. 循环顺序(求排列问题) 5. 验证dp数组
 * 3. 递推公式: dp[j]有几种来源，dp[j - 1]，dp[j - 2]，dp[j - 3] 等等，即：dp[j - i] (i <= m, m表示一次最多能爬上几层)
 */
class Solution2_1 {
    public:
    Solution2_1() {
        cout << "fullbag for claim stairs object created" << endl;
    }
    int floors(int a) {
        vector<int> dp(10000, 0);
        dp[0] = 1;
        int m = 2; // 表示一次最多能爬上几层
        for (int j = 0; j <= a; j++) {
            for (int i = 0; i <= m; i++) {
                if (j >= i) dp[j] += dp[j - i];
            }
        }
        return dp[a];
    }
};

/*
 * 花体力爬楼梯（每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯
 * 在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯
 */
class Solution3 {
    public:
        Solution3() {
            cout << "Claim stairs with strength object created" << endl;
        }
        // 传址调用
        int floors(vector<int>& cost) {
            int N = 100000;
            vector<int> dp(N + 1); // 到达第i个台阶所花费的最少体力
            dp[0] = 0;
            dp[1] = 0; // 从第0层或第1层开始爬，起始位置不耗费体力
            for (int i = 2; i <= cost.size(); i++) {
                dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]); // 前n-1个台阶耗费体力+爬上第n-1个台阶耗费的体力
            }
            return dp[cost.size()];
        }
};

/*
 * 二维DP
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）问总共有多少条不同的路径
 */
class Solution4  {
    public:
        Solution4() {
            cout << "Robot moving object created" << endl;
        }
        // 传值调用
        int ways(int m, int n) {
            vector<vector<int>> dp(m, vector<int> (n, 0));
            for (int i = 0; i < m; i++) dp[i][0] = 1;
            for (int j = 0; j < n; j++) dp[0][j] = 1; // 只横着走或只竖着走 每一步上只有一条路径可以到达
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // 可能从左边过来也可能从上面过来
                }
            }
            return dp[m - 1][n - 1];
        }
};

/*
 * 二维DP
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）
 * 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
 */
class Solution5 {
    public:
        Solution5() {
            cout << "robot moving with obstacles object created." << endl;
        }
        int obstaclesWay(vector<vector<int>>& way) {
            int N = 100000;
            int m = way.size(); // 宽
            int n = way[0].size();
            vector<vector<int>> dp(m, vector<int>(n, 0));
            for(int i = 0; i < m && way[i][0] == 0; i++) dp[i][0] = 1; // 初始化，第一行第一列没有障碍的地方都是1
            for(int j = 0; j < n && way[0][j] == 0; j++) dp[0][j] = 1;
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    if (way[i][j] == 1) continue; // 有障碍的地方跳过
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // 当前位置会有的不同的路径
                }
            }
            return dp[m - 1][n - 1];
        }
};
/*
 * 64. 最小路径和
 */
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(), vector<int> (grid[0].size(), 0));
        dp = grid;
        for (int i = 1; i < grid.size(); i++) {
            dp[i][0] = dp[i][0] + dp[i-1][0];
        }
        for (int j = 1; j < grid[0].size(); j++) {
            dp[0][j] = dp[0][j] + dp[0][j-1];
        }
        for (int i = 1; i < grid.size(); i++) {
            for (int j = 1; j < grid[0].size(); j++) {
                dp[i][j] = min(dp[i-1][j] + dp[i][j], dp[i][j-1] + dp[i][j]);
                // dp[i][j] += min(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[grid.size() - 1][grid[0].size() - 1];
    }
};


/*
 * 给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 
 * 返回你可以获得的最大乘积
 */
class Solution6 {
    public:
        Solution6() {
            cout << "Number split object created" << endl;
        }
        // 类内成员函数可以是传值传参也可以是地址传参, 同普通函数一样, 传值传参可以给实参, 地址传参只能给左值
        int split(int n) {
            vector<int> dp(n + 1);
            dp[2] = 1;  // 分拆数字i，可以得到的最大乘积为dp[i]。只会从2开始
            // 可以想 dp[i]最大乘积是怎么得到的呢？其实可以从1遍历j，然后有两种渠道得到dp[i].
            for (int i = 3; i <= n ; i++) {
                for (int j = 1; j < i - 1; j++) {
                    dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
                }
            }
            return dp[n];
        }
};

/* 
 * 96.不同的二叉搜索树
 * 给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
 * dp[3]，就是 元素1为头结点搜索树的数量 + 元素2为头结点搜索树的数量 + 元素3为头结点搜索树的数量
 * 元素1为头结点搜索树的数量 = 右子树有2个元素的搜索树数量 * 左子树有0个元素的搜索树数量
 * 元素2为头结点搜索树的数量 = 右子树有1个元素的搜索树数量 * 左子树有1个元素的搜索树数量
 * 元素3为头结点搜索树的数量 = 右子树有0个元素的搜索树数量 * 左子树有2个元素的搜索树数
 * 有2个元素的搜索树数量就是dp[2]。
 * 有1个元素的搜索树数量就是dp[1]。
 * 有0个元素的搜索树数量就是dp[0]。
 * 所以dp[3] = dp[2] * dp[0] + dp[1] * dp[1] + dp[0] * dp[2]
 */
class Solution7 {
    public:
        Solution7() {
            cout << "BST object created" << endl;
        }
        int BST(int n) {
            vector<int> dp(n + 1);
            dp[0] = 1;
            for (int i = 1; i <=n; i++) {
                for (int j = 1; j <= i; j++) {
                    dp[i] += dp[j - 1] * dp[i - j]; // dp[3] = dp[2] * dp[0] + dp[1] * dp[1] + dp[0] * dp[2]
                }
            }
            return dp[n];
        }
};

/*
 * 0-1背包问题，是二维DP问题 
 * 返回你可以获得的最大乘积
 * dp[i][j]的含义：从下标为[0-i]的物品里任意取，放进容量为j的背包，价值总和最大是多少。
 * 那么可以有两个方向推出来dp[i][j]
 * 不放物品i：由dp[i - 1][j]推出，即背包容量为j，里面不放物品i的最大价值，此时dp[i][j]就是dp[i - 1][j]。(其实就是当物品i的重量大于背包j的重量时，物品i无法放进背包中，所以被背包内的价值依然和前面相同。)
 * 放物品i：由dp[i - 1][j - weight[i]]推出，dp[i - 1][j - weight[i]] 为背包容量为j - weight[i]的时候不放物品i的最大价值，那么dp[i - 1][j - weight[i]] + value[i] （物品i的价值），就是背包放物品i得到的最大价值
 * dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
 */
class Solution8{
    public:
    Solution8() {cout << "01bag object created" << endl;}
    int bag() {
        vector<int> weight = {1, 3, 4};
        vector<int> value = {15, 20, 30};
        int bagweight = 4;
        // 二维数组
        vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0)); // 初始化为0
        // 初始化, 第一行是放入物品0，价值最大是多少, 不是全0
        // j = weight[0], 表明背包容量j>=weight[0]时都可以装进去
        for (int j = weight[0]; j <= bagweight; j++) {
            dp[0][j] = value[0];
        }
        // 递推
        for (int i = 1; i < weight.size(); i++) {
            for (int j = 0; j <= bagweight; j++) {
                // 一共有两种情况, 第一种是多出来的背包空间不足以放下新的物品, 就不放新物品
                // 另一种情况是多出来的空间可以放下新的物品, 这时候需要比较不放和放的结果哪个更大 就取哪个
                if (j < weight[i]) dp[i][j] = dp[i - 1][j]; 
                else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
        return dp[weight.size() - 1][bagweight];
    }
};

/*
 * 0-1背包问题，用一维DP解决
 * 在使用二维数组的时候，递推公式：dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
 * 其实可以发现如果把dp[i - 1]那一层拷贝到dp[i]上，表达式完全可以是：dp[i][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i]);
 * dp[j]可以通过dp[j - weight[i]]推导出来，dp[j - weight[i]]表示容量为j - weight[i]的背包所背的最大价值。
 * dp[j - weight[i]] + value[i] 表示 容量为 j - 物品i重量 的背包 加上 物品i的价值。（也就是容量为j的背包，放入物品i了之后的价值即：dp[j]）
 * 此时dp[j]有两个选择，一个是取自己dp[j] 相当于 二维dp数组中的dp[i-1][j]，即不放物品i
 * 一个是取dp[j - weight[i]] + value[i]，即放物品i，指定是取最大的，毕竟是求最大价值，
 * 两次循环遍历，先遍历物品再遍历容量，映射到二维DP来看就是先输出第一行(物品0)的dp数据, 再输出第二行(物品1)的dp数据, 但是覆盖掉原来的第一行
 * 为什么遍历容量是倒序不能是正序？
 * 因为从二维DP来看，dp[i][j]的值来自于dp[i-1][j](上方)和dp[i-1][j-weight[i]] + value[i](左上方)
 * 压缩后的一维DP到第二个物品时就会再写一行覆盖掉第一个物品的DP状态，也就是会把左上的值覆盖掉 这样就乱了
 */
class Solution9{
    public:
        Solution9() {
            cout << "1-dimension 01bag created" << endl;
        }
        int bag_1() {
            vector<int> weight = {1, 3, 4};
            vector<int> value = {15, 20, 30};
            int bagWeight = 4;
            vector<int> dp(bagWeight + 1, 0); // (0, 1, 2, 3, 4)
            dp[0] = 0; // 初始化,因为是0，所以不用刻意多写一步初始化
            // 先遍历物品
            for (int i = 0; i < weight.size(); i++) { 
            // 再遍历背包，不至于遍历所有的背包容量，因为背包容量小于物品重量时 没有意义，即这里要保证(j - weight[i] >= 0)
                for (int j = bagWeight; j >= weight[i]; j--) { 
                    dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
                }
            }
            return dp[bagWeight];
        }
};

/*
 * 分割等和子集
 * 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等
 * 经典用回溯，但怎么用动态规划来解题
 * 只要找到集合里能够出现 sum / 2 的子集总和，就算是可以分割成两个相同元素和子集了
 * 1. 背包的体积为sum / 2
 * 2. 背包要放入的商品（集合里的元素）重量为 元素的数值，价值也为元素的数值
 * 3. 背包如果正好装满，说明找到了总和为 sum / 2 的子集。
 * 4. 背包中每一个元素都不可重复放入
 */
class Solution10{
    public:
        Solution10() {
            cout << "subset object created " << endl;
        }
        bool subset(vector<int>& nums) {
            int sum = 0;
            vector<int> dp(100010, 0); // 一维dp 初始化为0
            for (auto i : nums) sum += i; // 得到总和
            if (sum % 2 != 0) return false; // 必须得是偶数
            int target = sum / 2;

            // 01背包找一半, 看能不能放进来一些元素，使得值加和正好等于target, target相当于背包容量
            for (int i = 0; i < nums.size(); i++) {
                for (int j = target; j >= nums[i]; j--) {
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                }
            }
            if (dp[target] == target) return true;
            return false;
        }
};
/*
 * 分割等和子集, 二维DP写法
 * 状态定义：dp[i][j]表示从数组的 [0, i] 这个子区间内挑选一些正整数，每个数只能用一次，使得这些数的和恰好等于 j。
 * 状态转移方程：很多时候，状态转移方程思考的角度是「分类讨论」，对于「0-1 背包问题」而言就是「当前考虑到的数字选与不选」。
 * 不选择 nums[i]，如果在 [0, i - 1] 这个子区间内已经有一部分元素，使得它们的和为 j ，那么 dp[i][j] = true；
 * 选择 nums[i]，如果在 [0, i - 1] 这个子区间内就得找到一部分元素，使得它们的和为 j - nums[i]。
 * 状态转移方程：dp[i][j] = dp[i - 1][j] or dp[i - 1][j - nums[i]]
 * 初始化条件: j - nums[i] 作为数组的下标，一定得保证大于等于 0 ，因此 nums[i] <= j；
 * 注意到一种非常特殊的情况：j 恰好等于 nums[i]，即单独 nums[j] 这个数恰好等于此时「背包的容积」 j，这也是符合题意的。
 * 初始化：dp[0][0] = false，因为候选数 nums[0] 是正整数，凑不出和为 00；
 * 输出：dp[len - 1][target]，这里 len 表示数组的长度，target 是数组的元素之和（必须是偶数）的一半。
 */ 
class Solution10_1 {
    public:
    Solution10_1() {
        cout << "2-dimension dp of subset created" << endl;
    }
    bool subset(vector<int>& nums) {
        int sum = 0;
        for (auto i : nums) sum += i; // 得到总和
        if (sum % 2 != 0) return false; // 必须得是偶数
        int target = sum / 2;
        vector<vector<int>> dp(nums.size(), vector<int>(target + 1, 0)); // 二维dp初始化, 行数为nums容量, 列数为target
        if (nums[0] <= target) dp[0][nums[0]] = true; // (0,0)处初始化
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i] == j) {
                    dp[i][j] = true;
                    continue;
                }
                if (nums[i] < j) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
                }
            }
        }
        return dp[nums.size() - 1][target];
    }
};

/*
 * 1049. 最后一块石头的重量 II: 有一堆石头，每块石头的重量都是正整数。
 * 每一回合从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
 * 如果 x == y，那么两块石头都会被完全粉碎； 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。 
 * 最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回 0。
 * 本题其实就是尽量让石头分成重量相同的两堆
 * 如何转换到01背包的动态规划问题？这类问题转化到动态规划的idea就是: 
 * 能放入背包(背包容量为所有石头的重量和的一半)的物品的价值(等价于物体重量)最大, 即放入背包的重量==重量总和的一半
 * 物体重量是store[i], 物体价值也是store[i], 背包容量是target(为所有石头的重量和的一半，初始重量为0(非负))
 * 5部曲：
 * 1. dp数组含义: dp[i]表示容量为j的背包最多可以背dp[j]重的石头
 * 2. 递推公式：dp[j] = max(dp[j], dp[j - store[i]] + store[i])
 * 3. 初始化: 最大容量（重量）是所有石头的重量和。1 <= stones.length <= 30，1 <= stones[i] <= 1000，所以最大重量就是30*1000。
 * 这里设定的是dp数组的最大范围 保证不会越界
 * 4. 确定遍历顺序
 * 5. 举例推导：最后dp[target]里是容量为target的背包所能背的最大重量。
 * 也就是分成两堆石头，一堆石头的总重量是dp[target] 另一堆就是sum - dp[target]。这种情况下两堆石头互相粉碎可以得到最小的剩余重量
 * 最终结果就是两者差值: (sum - dp[target]) - dp[target]
 */
class Solution11 {
    Solution11() {
        cout << "stone weight object created" << endl;
    }
    int stoneWeight(vector<int>& stone) {
        vector<int> dp(150001, 0); // dp数组声明and初始化
        int sum = 0;
        for (auto i : stone) sum += i;
        int target = sum / 2; // 背包容量确定
        // 开始递推
        for (int i = 0; i < stone.size(); i++) {
            for (int j = target; j >= stone[i]; j--) { // 这里要保证(j - stone[i] >= 0)
                dp[j] = max(dp[j], dp[j - stone[i]] + stone[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }
};
/*
 * 1049. 最后一块石头的重量 II： 二维DP做法
 * 此题思路就是转换为0-1背包问题。相当于在N个物品中找寻背包容量为target（所有数组元素和的一半向下取整）的最大价值。
 * 这里假设物品的价值跟体积值一样。是简化的情况。
 */
class Solution11_2 {
    Solution11_2() {
        cout << "2-dimension Stone weight object created" << endl;
    }
    int stoneWeight(vector<int>& stone) {
        if (stone.empty()) return 0;
        long sum = 0;
        long N = stone.size();
        for (auto i : stone) sum += i; // 得到总和
        long target = sum / 2; // 确定背包容量
        vector<vector<int>> dp(N, vector<int>(target + 1, 0)); 
        // 二维dp初始化
        for (int j = 1; j <= target; j++) {
            if (j >= stone[0]) {
                dp[0][j] = stone[0];
            }
        }
        for (int i = 1; i < N; i++) {
            for (int j = 1; j <= target; j++) {
                // 01背包一共有两种情况, 第一种是多出来的背包空间不足以放下新的物品, 就不放新物品
                // 另一种情况是多出来的空间可以放下新的物品, 这时候需要比较不放和放的结果哪个更大 就取哪个
                if (j < stone[i]) {
                    dp[i][j] = dp[i - 1][j]; // cannot choose item i
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stone[i]] + stone[i]);
                }
            }
        }
        return sum - dp[N - 1][target] - dp[N - 1][target];
    }
};

/*
 * 494. 目标和
 * 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 * 返回可以使最终数组和为目标数 S 的所有添加符号的方法数
 * 如何转化为01背包问题呢。
 * 假设加法的总和为x，那么减法对应的总和就是sum - x。sum是数组中数字的总和
 * 所以我们要求的是 x - (sum - x) = S ——> x = (S + sum) / 2
 * 此时问题就转化为，装满容量为x背包，有几种方法。(x是添加加法符号的数值的总和, 找到实现这种总和的几种方法就是有几个符号添加方法)
 * 确定dp数组以及下标的含义: dp[j] 表示 填满j（包括j）这么大容积的包，有dp[j]种方法
 * 递推：有哪些来源可以推出dp[j]呢？不考虑nums[i]的情况下，填满容量为j - nums[i]的背包，有dp[j - nums[i]]种方法。
 * 凑整dp[5]有多少方法呢，也就是把 所有的 dp[j - nums[i]]
 * 初始化：dp[0] = 1，理论上也很好解释，装满容量为0的背包，有1种方法，就是装0件物品。其他下标对应的数值应该初始化为0
 */
class Solution12 {
    public:
    Solution12() {
        cout << "target sum object created" << endl;
    }
    int targetSum(vector<int>& nums, int S) {
        int Sum = 0;
        for (auto i : nums) Sum += i;
        // 特殊情况
        if (abs(S) > Sum) return 0;
        if ((S + Sum) % 2 != 0) return 0;
        // 01背包
        int bagSize = (S + Sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (auto i : nums) {
            for (int j = bagSize; j >= i; j--) {
                dp[j] = dp[j - i];
            }
        };
        return dp[bagSize];
    }
};
/*
 * 494. 目标和 二维DP做法
 * 要求的是 x - (sum - x) = S ——> x = (S + sum) / 2
 * 此时问题就转化为，装满容量为x背包，有几种方法。(x是添加加法符号的数值的总和, 找到实现这种总和的几种方法就是有几个符号添加方法)
 * 确定dp数组以及下标的含义: dp[j] 表示 填满j（包括j）这么大容积的包，有dp[j]种方法
 * 递推：有哪些来源可以推出dp[j]呢？不考虑nums[i]的情况下，填满容量为j - nums[i]的背包，有dp[j - nums[i]]种方法。
 * 凑整dp[5]有多少方法呢，也就是把 所有的 dp[j - nums[i]]
 * 初始化：dp[0] = 1，理论上也很好解释，装满容量为0的背包，有1种方法，就是装0件物品。其他下标对应的数值应该初始化为0
 */
class Solution12_2 {
    public:
    Solution12_2() {
        cout << "target sum with 2-dimension object created" << endl;
    }
    int targetSum(vector<int>& nums, int S) {
        int Sum = 0;
        for (auto i : nums) Sum += i;
        // 特殊情况
        if (abs(S) > Sum) return 0;
        if ((S + Sum) % 2 != 0) return 0;
        // 01背包
        int bagSize = (S + Sum) / 2;
        int len = nums.size();
        vector<vector<int>> dp(len, vector<int> (bagSize + 1, 0)); // 设定二维Dp数组
        dp[0][0] = 1; //初始化
        for (int i = 1; i < len; i++) {
            for (int j = 0; j <=bagSize ; j++) {
                if (j < nums[i]) dp[i][j] = dp[i - 1][j];
                else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
            }
        }
        return dp[len - 1][bagSize];
    }
};

/*
 * 完全背包问题：与01背包不同的是, 每种物品有无限件, 而不是01背包的只有一件
 * 主要产生的区别就是, 在一维DP实现的过程中, 内层背包容量的遍历可以正序; 而且两层迭代的先后顺序可以调换
 */
class Solution20 {
    public:
    Solution20() {
        cout << "full bag object created" << endl;
    }
    int fullBag() {
        vector<int> weight = {1, 3, 4};
        vector<int> value = {15, 20, 30};
        int bagWeight = 4;
        vector<int> dp(bagWeight + 1, 0); // 初始化
        for (int i = 0; i < weight.size(); i++) {
            for (int j = weight[i]; j <= bagWeight; j++) {
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
        return dp[bagWeight];
    }
};

/*
 * 求组合数：动态规划：518.零钱兑换II (opens new window)
 * 求排列数：动态规划：377. 组合总和 Ⅳ (opens new window)、动态规划：70. 爬楼梯进阶版（完全背包） (opens new window)
 * 求最小数：动态规划：322. 零钱兑换 (opens new window)、动态规划：279.完全平方数
 */
/*
 * 518. 零钱兑换 II 给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
 * 无限个硬币 所以是完全背包
 * 五部曲
 * 1. dp数组含义：dp[j] 凑成总金额的货币组合数
 * 2. 递推公式: dp[j] = dp[j - coins[i]]
 * 3. 初始化: dp[0] = 1
 * 4. 确定遍历顺序: 以防万一, 建议全部外循环物品(钱币), 内循环背包(总金额)
 * 但是根据本题题意, 外层for循环遍历物品（钱币），内层for遍历背包（金钱总额）得到组合数(不要求顺序), 相反的遍历得到排列数(要求排序)
 * 5. 举例推导dp数组
 */
// 外层for循环遍历物品（钱币），内层for遍历背包（金钱总额）得到组合数(不要求顺序)
class Solution21_1 {
    public:
    Solution21_1() {
        cout << "coins object21_2 created" << endl;
    }
    int coins(vector<int>& coins, int sum) {
        vector<int> dp(sum + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= sum; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[sum];
    }
};
// 反的遍历得到排列数(要求排序)
class Solution21_2 {
    public:
    Solution21_2() {
        cout << "coins object21_2 created" << endl;
    }
    int coins(vector<int>& coins, int sum) {
        vector<int> dp(sum + 1, 0);
        dp[0] = 1;
        for (int j = 0; j <= sum; j++) {
            for (int i = 0; i < coins.size(); i++) {
                if (j >= coins[i]) dp[j] += dp[j - coins[i]];
            }
        }
        return dp[sum];
    }
};
/*
 * 322. 零钱兑换 I 给定不同面额的硬币 coins 和一个总金额 amount。计算可以凑成总金额所需的最少的硬币个数。
 * 如果没有任何一种硬币组合能组成总金额，返回 -1。
 * 无限个硬币 所以是完全背包 与518 零钱兑换 II 不同的是, I 只要最少能够兑换的个数, 所以递推肯定要找最小值, 但当前状态的来源不变的
 * 五部曲
 * 1. dp数组含义：dp[j] 凑成总金额j的所需的最少币数
 * 2. 递推公式: dp[j] = min(dp[j - coins[i]] + 1, dp[j]) 
 * tips: dp[j - coins[i]] + 1是拿当前的货币, 所以是[j - coins[j](不拿当前货币时的最少币数) + 1]; dp[j]就是不拿当前货币 和上次的一样
 * 3. 初始化: dp[0] = 0, 这不能只初始化这一个了 考虑到递推公式的特性，dp[j]必须初始化为一个最大的数，否则就会在min(dp[j - coins[i]] + 1, dp[j])比较的过程中被初始值覆盖。
 * 4. 确定遍历顺序: 本题求钱币最小个数，那么钱币有顺序和没有顺序都可以，都不影响钱币的最小个数
 * so, 外循环物品(钱币), 内循环背包(总金额)
 * 根据排列组合总结, 外层for循环遍历物品（钱币）,内层for遍历背包（金钱总额）得到组合数(不要求顺序), 相反的遍历得到排列数(要求排序)
 * 5. 举例推导dp数组
 */
class Solution21_3 {
    public:
    Solution21_3() {
        cout << "coins object21_3 created" << endl;
    }
    int coinChange(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, INT_MAX); // 直接DP里把剩下的也初始化了
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) { // 别忘了这里因为递推的缘故要保证 j - coins[i] >= 0
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return dp[amount];
    }
};

/*
 * 279. 完全平方数: 给定正整数 n，找到若干个完全平方数(比如 1, 4, 9)使得它们的和等于 n。你需要让组成和的完全平方数的个数最少
 * 完全平方数就是物品（可以无限件使用），凑个正整数n就是背包，问凑满这个背包最少有多少物品？
 * 
 */
class Solution22 {
public:
    Solution22() {
        cout << "square figures object created" << endl;
    }
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) { // 遍历背包
            for (int j = 1; j * j <= i; j++) { // 遍历物品
                dp[i] = min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};


/*
 * 组合总和 Ⅳ： 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
 * 注意: 本题题目描述说是求组合，但又说是可以元素相同顺序不同的组合算两个组合，其实就是求排列！
 * 五部曲:
 * 1. 确定dp含义: dp[j] 凑成target = j的排列数
 * 2. 递推公式: dp[j] = dp[j - nums[i]]
 * 3. 初始化: dp[0] = 1但是这里仅仅为了递推 没有实际物理含义(不好解释就是)
 * 4. 确定遍历顺序
 * 5. dp数组验证
 */
class Solution23 {
    public:
    Solution23() {
        cout << "Permutation and combination object created" << endl;
    }
    int Csum(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 1; j <= target; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j >= nums[i]) dp[j] += dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};

/*
 * 139. 单词拆分 给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词
 * 示例 2： 输入: s = "applepenapple", wordDict = ["apple", "pen"] 输出: true 解释: 返回 true 
 * 因为 "applepenapple" 可以被拆分成 "apple pen apple"。   
 * 注意你可以重复使用字典中的单词。
 * 列表中的单词就是物品(? 代码里看起来字符串s中的字母是物品), 字符串s就是背包, 转化为背包问题就是看, 在能够多次利用的列表中的单词里, 能不能选出组合组成字符串。是一个布尔值问题
 * 五部曲: 1. dp[j] = 字符串长度为i时能不能由组成单词列表中的word组成
 * 2. 递推公式: if ([j, i] 这个区间的子串出现在字典里 && dp[j]是true) { dp[i] = true }
 * 3. 初始化: dp[0] = true
 * 4. 遍历顺序: 完全背包，内外都是正序。不要求排列组合，先背包还是先物品都可以。5. 验证dp数组
 */
class Solution24 {
    Solution24() {
        cout << "word embed object created" << endl;
    }
    bool wordSet(string s, vector<int>& wordDict) {
        // set是值集合, map是键值对
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {   // 遍历背包
            for (int j = 0; j < i; j++) {       // 遍历物品
                string word = s.substr(j, i - j); //substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};

/*
 * 198. 打家劫舍
 * 五部曲: 1. dp含义: dp[j] = 考虑下标j以内的前j个房屋, 最多可以偷盗的金钱
 * 2. 递推公式: dp[j] = max(dp[j - 1], dp[j - 2] + nums[i]). 决定dp[i]的因素就是第i房间偷还是不偷。
 * tips: 如果偷第i房间，那么dp[j] = dp[j - 2] + nums[j]. 
 * 第i-1房一定是不考虑的，找出 下标j-2（包括j-2）以内的房屋，最多可以偷窃的金额为dp[j-2] 加上第i房间偷到的钱。
 * 如果不偷第i房间，那么dp[j] = dp[j - 1]，即考虑j-1房。然后dp[j]取最大值
 * 3. 初始化: 递推公式的基础就是dp[0] 和 dp[1]
 * tips: 从dp[i]的定义上来讲，dp[0] 一定是 nums[0]，dp[1]就是nums[0]和nums[1]的最大值即：dp[1] = max(nums[0], nums[1]);
 * 4. 遍历顺序: 从前往后 不是背包问题 5. 验证dp数组
 */
class Solution25{
    public:
    Solution25() {
        cout << "rob I object created" << endl;
    }
    int rob1(vector<int>& rooms) {
        // 考虑特殊情况
        if (rooms.size() == 0) return 0;
        if (rooms.size() == 1) return rooms[0];
        vector<int> dp(rooms.size(), 0);
        dp[0] = rooms[0], dp[1] = max(rooms[0], rooms[1]);
        for (auto i = 2; i < rooms.size(); i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + rooms[i]);
        }
        return dp[rooms.size() - 1];
    }
};


/*
 * 买卖股票是比较特殊的dp数组, 有两种状态
 * 121. 买卖股票的最佳时机 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
 * 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
 * 五步法: 1. dp数组含义: dp[i][0] 表示第i天持有股票所得最多现金，dp[i][1] 表示第i天不持有股票所得最多现金
 * 2. 递推公式。如果第i天持有股票即dp[i][0]，那么可以由两个状态推出来：dp[i][0] = max(dp[i - 1][0], -prices[i]) 这里因为只买一次只卖一次, 所以买的时候必然为0-prices[i], 即dp[i - 1][1] == 0
 * 如果第i天不持有股票即dp[i][1]， 也可以由两个状态推出来: dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i])
 * 3. 初始化: dp来自于dp[0][0] and dp[0][1]. dp[0][0] = -prices[0], dp[0][1] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26{
    Solution26() {
        cout << "Stocks sale object created" << endl;
    }
    int Stocks(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[len - 1][1];
    } 
};
/*
 * 122 和 121 只有一点递推公式的区别
 * 122. 买卖股票的最佳时机 II 给定一个数组 prices，多次买卖后，所能获取的最大利润。题意是 多次买后可以多次卖，买可以重叠
 * 五步法: 1. dp数组含义: dp[i][0] 表示第i天持有股票所得最多现金，dp[i][1] 表示第i天不持有股票所得最多现金。
 * 2. 递推公式。如果第i天持有股票即dp[i][0]，那么可以由两个状态推出来：dp[i][0] = max(dp[i - 1][0], dp[i - 1][0] - prices[i]) 上次未持有股票的时候dp[i - 1][0] 减去这次买股票的前prices[i]
 * 如果第i天不持有股票即dp[i][1]， 也可以由两个状态推出来: dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i])
 * 3. 初始化: dp来自于dp[0][0] and dp[0][1]. dp[0][0] = -prices[0], dp[0][1] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26_1{
    Solution26_1() {
        cout << "Stocks sale object created" << endl;
    }
    int Stocks(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[len - 1][1];
    } 
};
/*
 * 123. 买卖股票的最佳时机 III 给定一个数组 prices，最多两笔交易后，所能获取的最大利润。题意是:不能同时参与多笔交易（必须在再次购买前出售掉之前的股票,相当于多次的121题）
 * 五步法: 1. dp数组含义:一天一共就有五个状态，
 * (j=0)没有操作，(j=1)第一次买入，(j=2)第一次卖出，(j=3)第二次买入，(j=4)第二次卖出
 * 2. 递推公式。如果第i天的j=0状态即dp[i][0]: dp[i][0] = dp[i - 1][0]
 * 如果第i天的j=1状态即dp[i][1]，可以由两个状态推出来: dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]), j=2,3,4同理可推
 * 3. 初始化: dp来自于dp[0][j], dp[0][0] =0, dp[0][1] = -prices[0], dp[0][2] = 0, dp[0][3] = -prices[0], dp[0][4] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26_2{
    Solution26_2() {
        cout << "Stocks sale object created" << endl;
    }
    int Stocks(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(5, 0));
        dp[0][1] = -prices[0];
        dp[0][0] = 0;
        dp[0][2] = 0;
        dp[0][3] = -prices[0];
        dp[0][4] = 0;
        for (int i = 1; i < len; i++) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
        }
        return dp[len - 1][4];
    } 
};
/* 
 * 188 和 123的区别就是把进行的交易次数增大到了K次，这时候就得for循环把所有设定写出来
 * 188. 买卖股票的最佳时机 IV 给定一个数组 prices，最多K笔交易后，所能获取的最大利润。题意是:不能同时参与多笔交易（必须在再次购买前出售掉之前的股票,相当于多次的121题）
 * 五步法: 1. dp数组含义:一天一共就有K个状态，
 * (j=0)没有操作，(j=1)第一次买入，(j=2)第一次卖出，(j=3)第二次买入，(j=4)第二次卖出。......
 * 2. 递推公式。如果第i天的j=0状态即dp[i][0]: dp[i][0] = dp[i - 1][0]
 * 如果第i天的j=1状态即dp[i][1]，可以由两个状态推出来: dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]), j=2,3,4同理可推
 * 3. 初始化: dp来自于dp[0][j], dp[0][0] =0, dp[0][1] = -prices[0], dp[0][2] = 0, dp[0][3] = -prices[0], dp[0][4] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26_3{
    Solution26_3() {
        cout << "Stocks sale object created" << endl;
    }
    int Stocks(vector<int>& prices, int k) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(2 * k + 1, 0)); 
        dp[0][0] = 0;
        for (int j = 1; j < 2 * k; j += 2) {
            dp[0][j] = -prices[0];
        }
        for (int i = 1; i < len; i++) {
            for (int j = 0; j < 2 * k - 1; j += 2) {
                dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] - prices[i]);
                dp[i][j + 2] = max(dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i]);
            }
        }
        return dp[len - 1][2 * k];
    } 
};
/* 
 * 309 和 188 的区别就是多了冷冻期这么一个新的状态
 * 309. 最佳买卖股票时机含冷冻期 给定一个数组 prices，最多K笔交易后（包含冷冻期），所能获取的最大利润。(多次买卖+冷冻期的121题）
 * 五步法: 1. dp数组含义: dp[i][j] 前 i 天持有股票状态j（j = 0, 1）(0是持有, 1是未持有)
 * 2. 递推公式。dp[i + 1][1] = max(dp[i][0] + prices[i], dp[i][1]); // max(昨天持有今天卖掉, 昨天没持有今天也不买)
 *             dp[i + 1][0] = max(dp[i - 1][1] - prices[i], dp[i][0]); // 冷冻期, 所以多往前推一天; max(隔一天前不持有但是今天买入, 昨天没卖今天继续不卖)
 * tips: 因为这里当前的状态需要考虑到 i - 2 的状态，为了避免数组越位, 所以把整个 i 向后移 从 i = 1 第一天开始
 * 此时 i = 0 并不代表的prices[0], 此时仅是占位 没有意义
 * 3. 初始化: dp来自于dp[0][j]，dp[1][0] = -prices[0]; dp[1][1] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26_4 {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size() + 1, vector<int> (2, 0));
        // 0 是持有 1 是未持有
        dp[1][0] = -prices[0];
        dp[1][1] = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[i + 1][1] = max(dp[i][0] + prices[i], dp[i][1]); // max(昨天持有今天卖掉, 昨天没持有今天也不买)
            dp[i + 1][0] = max(dp[i - 1][1] - prices[i], dp[i][0]); // 冷冻期, 所以多往前推一天; max(隔一天前不持有但是今天买入, 昨天没卖今天继续不卖)
        }
        return dp[prices.size()][1];
    }
};
/*
 * 714.买卖股票的最佳时机含手续费
 * 714 和 122 只有手续费的区别
 * 122. 买卖股票的最佳时机 II 给定一个数组 prices，多次买卖后，所能获取的最大利润。题意是 多次买后可以多次卖，买可以重叠
 * 五步法: 1. dp数组含义: dp[i][0] 表示第i天持有股票所得最多现金，dp[i][1] 表示第i天不持有股票所得最多现金。
 * 2. 递推公式。如果第i天持有股票即dp[i][0]，那么可以由两个状态推出来：dp[i][0] = max(dp[i - 1][0], dp[i - 1][0] - prices[i]) 上次未持有股票的时候dp[i - 1][0] 减去这次买股票的前prices[i]
 * 如果第i天不持有股票即dp[i][1]， 也可以由两个状态推出来: dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i])
 * 3. 初始化: dp来自于dp[0][0] and dp[0][1]. dp[0][0] = -prices[0], dp[0][1] = 0
 * 4. 确定遍历顺序: 从前向后 非背包. 5. 验证DP
 */
class Solution26_5 {
    Solution26_5() {
        cout << "Stocks sale object created" << endl;
    }
    int Stocks(vector<int>& prices, int fee) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }
        return dp[len - 1][1];
    } 
};


int main() {
    int a, b, c, d, e, f, g, h, i, j= 0;
    int c_n[3] = {10, 15, 20};
    vector<int> c_l(c_n, c_n + 3);
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;
    Solution6 s6;
    Solution7 s7;
    Solution8 s8;
    Solution9 s9;
    Solution20 s20;
    a = s1.fib(10);
    b = s2.floors(10);
    c = s3.floors(c_l);
    d = s4.ways(7, 3);
    // e
    f = s6.split(10);
    g = s7.BST(3);
    h = s8.bag();
    i = s9.bag_1();
    j = s20.fullBag();
    printf("%d %d %d %d %d %d %d %d %d", a, b, c, d, f, g, h, i, j);
    return 0;
}