# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
# include<algorithm>
using namespace std;
/*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/*
 * 前缀和(动态数组和)
 */
class dayone0_0 {
public:
    vector<int> runningSum(vector<int>& nums) {
        for (auto i = 1; i < nums.size(); ++i) nums[i] += nums[i - 1]; 
        return nums;
    }
};
class dayone0_1 {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res;
        res[0] = nums[0];
        for (auto i = 1; i < nums.size(); ++i) {
            res[i] = res[i] + nums[i];
        }
        return res;
    }
};
/*
 * 724. 寻找数组的中心下标
 */
class dayone1_0 {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = 0;
        int left = 0;
        for (auto i : nums) sum += i;
        //cout << sum << endl;
        for (auto i = 0; i < nums.size(); ++i) {
            if (left * 2 + nums[i] == sum) return i;
            left += nums[i];
          //  cout << left << endl;
        }
        return -1;
    }
};
/*
 * 同构数组
 * 双向哈希映射
 */ 
class dayone2_0 {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> map1;
        unordered_map<char, char> map2;
        for (auto i = 0, j =0; i < s.size(); i++, j++) {
            map1[s[i]] = t[j];
            map2[t[j]] = s[i];
        }
        for (auto i = 0, j =0; i < s.size(); i++, j++) {
            // cout << map1[s[i]] << endl << t[j] << endl;
            // cout << map2[t[j]] << endl << s[i] << endl;
            if (map1[s[i]] != t[j] || map2[t[j]] != s[i]) return false;
        }
        return true;
    }
};
/*
 * 合并两个有序链表
 * 这道题是合并链表，通过新建一个链表的头结点（虚拟节点，哨兵节点新建法（也就是虚拟节点的next指向的是头结点））
 * 用新建的头结点来连接合并的链表。这时需要的是一个真实存在的头结点来作为哨兵（虚拟）节点，来产生新链表
 */ 
class dayone4_0 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* prehead = new ListNode(-1); // 构造函数
        ListNode* pre = prehead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                pre->next = l1;
                l1 = l1->next;
            }
            else {
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
            
        }
        pre->next = l1 == nullptr ? l2 : l1;
        return prehead->next;
    }
};
/*
 * 反转链表
 * 这道题是反转链表，通过新建一个空指针，来进行指向的位置，依次翻转next指针指向
 * 而这里就是和上一题不一样的地方。需要的不是真实存在的节点 而是空区域的指针。一旦用了真实存在节点，链表就会多出一个节点
 * 其实上一题的虚拟头节点也是一样的。因为最后的结果只需要虚拟头节点next的部分，其本身只是为了指向真实头结点的。
 */ 
class dayone5_0 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        while (head != nullptr) {
            ListNode* next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }
};
// 递归 详细一个递归过程
/*
 * 以输入1->2->3为例来分析递归的过程，设定revserse()函数等价于f()函数 简化书写
 * 开始处理, 输入1->2->3: 开始进栈
 *  f(1)
 *  f(1).last = f(2);
 *  f(2).last = f(3);
 *  因为f(3)时, 3->next == null，所以返回f(3)的head也就是3, 开始出栈 返回
 *  f(2).last = 3; 2->next->next = 2, 2->next = nullptr即3->2->NULL; 最后return last 即f(2) = 3; 此时整体链表化为1->2->NULL, 另一分支3->2->NULL
 *  向上一层
 *  f(1).last = f(2) = 3; 1->next->next = 1, 1->next = nullptr即2->1->NULL; 最后return last 即f(1) = 3; 此时链表化为3->2->1->NULL 分支已合并
 *  最终结果 f(1) = 3, 即返回的是从节点3开始的链表，由上可知, 此时链表为3->2->1->NULL, 已经完成反转
 */
class dayone5_1 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head; // 到终点返回
        ListNode* last = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};
/*
 * 链表的中间节点
 * 快慢指针
 */
class dayone6_0 {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
/*
 * 链表的中间节点
 * 快慢指针，其实是道数学题。步长为2的快指针与步长为1的满指针 肯定会在环内相交。（追及问题）
 * 相交位置，步长为1的指针从head走和步长为1的指针从相交点走 肯定会在环的入口处相交。
 */
class dayone7_0 {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL) {
            slow = slow->next;
            if (fast->next == NULL) return NULL;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* ptr = head;
                while (slow != ptr) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return NULL;
    }
};
/*
 * 买卖股票的最佳时机
 * 动态规划。只是形式上的二维DP，因为第二维度只是表明股票持有的状态
 * 五部曲：1. 确定dp含义；2. 确定递推公式；3. 确定初始值；4. 确定遍历顺序；5. 验证DP数组
 */
class dayone8_0 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        // 第一步 确定DP含义
        vector<vector<int>> dp(len, vector<int>(2));
        // 第三步 确定初始值
        // dp[0][1] 是 第一天买了（已持有）, dp[0][0]是第一天没买（未持有）
        dp[0][1] = -prices[0];
        dp[0][0] = 0;
        // 第四步 确定遍历顺序
        for (int i = 1; i < len; i++) {
            // 第二步 确定递推公式
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], -prices[i]);
        }
        return dp[len - 1][0];
    }
};
/*
 * 最长回文串
 * 哈希表记录 or 贪心
 * 原理是：hash里如果全是偶数或者有一种奇数，那自然就是原长度。如果有一种以上奇数，就不能组成回文串，就要删掉这些多出来的奇数，所以count - 1
 */
class dayone9_0 {
public:
    int longestPalindrome(string s) {
        int len = s.length();
        unordered_map<char, int> hash;
        for (char c : s) hash[c]++;
        int ans = 0;
        int label = 0;
        for (auto &[k, v] : hash) {
            if (v % 2 == 0) {
                ans += v;
            }
            else {
                label++;
                ans += v;
            }
        }
        if (label > 0) {
            ans -= label - 1;
        }
        return ans;
    }
};
// 异曲同工. 原理是：hash里如果全是偶数或者有一种奇数，那自然就是原长度。
// 如果有一种以上奇数，就不能组成回文串，就要删掉这些多出来的奇数，所以count - 1
class dayone9_1 {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> hash;
        for (auto c : s) hash[c]++;
        int count = 0;
        for (auto &[k, v] : hash) {
            count += (v % 2); // 有几个奇数
        }
        return count == 0 ? s.length() : (s.length() - (count - 1));
    }
};
/*
 * N叉树的前序遍历
 * 递归
 */
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class dayone10_0 {
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
        if (root == nullptr) return res;
        res.push_back(root->val);
        for (int i = 0; i < root->children.size(); i++) {
            preorder(root->children[i]);
        }
        return res;
    }
};
/*
 * 二叉树的层序遍历
 * 迭代 手动构造队列
 * 二叉树的前中后序遍历 的迭代法 是手动构造栈
 */
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class dayone11_0 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        vector<vector<int>> res;
        if (root != nullptr) que.push(root);
        while (!que.empty()) {
            int len = que.size();
            vector<int> vec;
            for (int i = 0; i < len; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            res.push_back(vec);
        }
        return res;
    }
};
/*
 * 704. 二分查找
 * 红蓝区域法
 * 注意点：1. left and right 位置；2. while 中止条件；3. 循环中应该写好 大于 等于 小于 分别的处理方式
 */
class dayone12_0 {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int l = -1, r = len;
        while (l + 1 != r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target) r = mid;
            else if (nums[mid] < target) l = mid;
            if (nums[mid] == target) return mid;
        }
        return -1;
    }
};
/*
 * 278. 第一个错误的版本
 * 红蓝区域法 upperbound and lowerbound问题
 * 注意点：1. left and right 位置；2. while 中止条件；3. 循环中应该写好 大于 等于 小于 分别的处理方式 4. 注意区分 upperbound and lowerbound
 */
class dayone13_0 {
private:
    bool isBadVersion(int version) {
        if (version == false) return true;
        else return false;
    }
public:
    int firstBadVersion(int n) {
        int l = -1, r = n;
        while (l + 1 != r) {
            int mid = l + (r - l) / 2;
            if (isBadVersion(mid))  r = mid;
            else l = mid;
        }
        return r;
    }
};
/*
 * 98. 验证二叉搜索树
 * BST搜索二叉树：节点左子树小于当前节点数，节点右子树大于当前节点数 （中序遍历为升序）
 */
// 普通左中右递归 判断节点值
class dayone14_0 {
private:
    long long maxVal = INT_MIN;
    bool DFS(TreeNode* root) {
        if (root == nullptr) return true;
        bool left = DFS(root->left);
        if (root->val > maxVal) return true;
        else return false;
        bool right = DFS(root->right);
        return left && right;
    }
public:
    bool isValidBST(TreeNode* root) {
        return DFS(root);
    }
};
// 中序遍历为升序的思路, 
// 这么写会超时，但不是因为方法 而是因为存了两次vector (res, vec) 
// class Solution {
// private:
//     vector<long long> res;
//     vector<long long> DFS(TreeNode* root) {
//         if (root == nullptr) return res;
//         DFS(root->left);
//         res.push_back(root->val);
//         DFS(root->right);
//         return res;
//     }
// public:
//     bool isValidBST(TreeNode* root) {
//         vector<long long> vec = DFS(root);
//         for (auto i = 1; i < vec.size(); i++) {
//             if (vec[i] - vec[i - 1] <= 0) return false;
//         }
//         return true;
//     }
// };
// 存一个就不会超时
class dayone14_1 {
private:
    vector<long long> res;
    void DFS(TreeNode* root) {
        if (root == nullptr) return;
        DFS(root->left);
        res.push_back(root->val);
        DFS(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        DFS(root);
        for (int i = 1; i < res.size(); i++) {
            if(res[i] <= res[i-1]) return false;
        }
        return true;
    }
};
/*
 * 235. 二叉搜索树的最近公共祖先
 * 注意遍历一条边和遍历整棵树的区别
 */
class dayone15_1 {
private:
    TreeNode* DFS(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return root;
        if (root->val > p->val && root->val > q->val) {
            TreeNode* left = DFS(root->left, p, q);
            if (left != nullptr) return left;
        }
        if (root->val < p->val && root->val < q->val) {
            TreeNode* right = DFS(root->right, p, q);
            if (right != nullptr) return right;
        }
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return DFS(root, p, q);
    }
};
/*
 * 733. 图像渲染
 * 二维数组的遍历 BFS and DFS
 */
// BFS广度优先搜索，就是一层层搜，要注意的是二叉树的层序遍历由于返回数据的问题在BFS模板上的轻微不同
class dayone16_1 {
public:
    const int dx[4] = {0, 0, -1, 1}; // 上下左右
    const int dy[4] = {1, -1, 0, 0}; // 上下左右
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        queue<pair<int, int>> que;
        int oldcolor = image[sr][sc];
        if (oldcolor == color) return image;
        image[sr][sc] = color;
        que.emplace(sr, sc);
        int m = image.size(), n = image[0].size(); 
        while (!que.empty()) {
            for (int i = 0; i < 4; i++) {
                int x = que.front().first, y = que.front().second;
                que.pop();
                int mx = x + dx[i], my = y + dy[i];
                if (mx >= 0 && mx < m && my >= 0 && my < n && image[mx][my] == oldcolor) {
                    que.emplace(mx, my);
                    image[mx][my] = color;
                }
            }
        }
        return image;
    }
};
// DFS深度优先搜索，就是在一个方向上搜到底 然后换另一个方向
class dayone16_2 {
public:
    const int dx[4] = {0, 0, -1, 1};  // 上下左右
    const int dy[4] = {1, -1, 0, 0};
    void DFS(vector<vector<int>>& image, int x, int y, int oldcolor, int newcolor) {
        image[x][y] = newcolor;
        for (int i = 0; i < 4; i++) {
            int mx = x + dx[i], my = y + dy[i];
            if (mx >= 0 && mx < image.size() && my >= 0 && my < image[0].size() && image[mx][my] == oldcolor) {
                DFS(image, mx, my, oldcolor, newcolor);
            }
        }
    } 

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldcolor = image[sr][sc];
        if (oldcolor != newColor) DFS(image, sr, sc, oldcolor, newColor);
        return image;
    }
};
/*
 * 200. 岛屿数量
 * 二维数组的遍历 BFS and DFS
 */
class dayone16_1 {
private:
    
    void DFS(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') return;
        grid[i][j] = '0';
        DFS(grid, i + 1, j);
        DFS(grid, i, j + 1);
        DFS(grid, i - 1, j);
        DFS(grid, i, j - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int m = grid.size(), n = grid[0].size();
        if (!m) return 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    DFS(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
};
/*
 * 509. 斐波那契数
 * 递归 or 动态规划
 */
// 动态规划
class dayone17_1 {
public:
    int fib(int n) {
        if (n <= 1) return n;
        vector<int> dp(n + 1);   // [0, n]
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
// 递归
class dayone17_2 {
public:
    int fib(int n) {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    }
};
/*
 * 70. 爬楼梯
 * 递归 or 动态规划
 */
// 动态规划
class dayone18_1 {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        int step = 2;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= step; j++) {
                if (i >= j) dp[i] += dp[i - j];
            }
        }
    }
};
class dayone18_2 {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 110, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i -2];
        }
        return dp[n];
    }
};
/*
 * 70. 使用最小体力爬楼梯
 * 动态规划
 */
// dp[i]的定义：到达第i个台阶所花费的最少体力为dp[i]
/*dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
注意这里为什么是加cost[i]，而不是cost[i-1],cost[i-2]之类的，因为题目中说了：每当你爬上一个阶梯你都要花费对应的体力值 
*/
class day19_1 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size());
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < cost.size(); i++) {
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        // 注意最后一步可以理解为不用花费，所以取倒数第一步，第二步的最少值
        return min(dp[cost.size() - 1], dp[cost.size() - 2]);
    }
};
/*
 * 62. 不同路径
 * 动态规划
 */
// 二维dp dp[i][j] ：表示从（0 ，0）出发，到(i, j) 有dp[i][j]条不同的路径。
class day20_1 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n));
        if(m <= 1 && n <= 1) return 1;
        for (int i = 1; i < m; i++) dp[i][0] = 1;  // 不应该从0开始 
        for (int j = 1; j < n; j++) dp[0][j] = 1;  // 不应该从0开始
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
/*
 * 1. 两数之和
 * 双指针 or 哈希
 */
// 双指针
class day21_1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> tmp;
        tmp = nums;
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        vector<int> res;
        while (l < r) {
            if (nums[l] + nums[r] == target) {
                break;
            } 
            else if (nums[l] + nums[r] < target) {
                l++;
            }
            else if (nums[l] + nums[r] > target) {
                r--;
            }
        }
        bool left = true;
        bool right = true; // 标志位控制一个左一个右
        if (l < r) {
            for (int i = 0; i < tmp.size(); i++) {
                if (left && nums[l] == tmp[i]) {
                    res.push_back(i);
                    left = false;
                }
                else if (right && nums[r] == tmp[i]){
                    res.push_back(i);
                    right = false;
                }
            }
        }
        return res;
    }
};
// hash表
class day21_2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        // 如果是这样写的话 nums=[3,2,4], target == 6的测试下，nums[0]==3, target - nums[0] == 3 == nums[0]
        // 此时返回的就是nums[0]的位置 与题意不符
        // for (int i = 0; i < nums.size(); i++) {
        //     hash[nums[i]] = i;
        // }
        // for (int i = 0; i < nums.size(); i++) {
        //     if (hash.find(target - nums[i]) != hash.end()) return {i, hash.find(target - nums[i])->second};
        // }
        // return {};
        // 将hash的insert写在一起 可以避免上述情况发生
        // 其中->second指的是hash的后一位数据，也就是hash{key, value}中的value, ->first则是指向key
        for (int i = 0; i < nums.size(); i++) {
            if (hash.find(target - nums[i]) != hash.end()) return {i, hash.find(target - nums[i])->second};
            hash[nums[i]] = i;
        }
        return {};
    }
};
// 暴力
class day21_3 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] == target - nums[i]) return {i, j};
            }
        }
        return {};
    }
};
/*
 * 299. 猜数字游戏
 * 字符串 哈希
 * 下面就说说为什么字符减'0'可以到相应的整数。现在比如我们要字符‘1’转换成数字1，就这么一个变化，
 * 我们看到了大家注意了字符型常量用''括起来的原因是，它们在计算机中都以各自的ASCII表示。而‘1’的对应编码是49的二进制码，但是我们的数字1，就等于1呀，
 * 所以为了由原来的‘1’实际上就是49的二进制变成现在的1对应的二进制1，只好用49-48=1了。
 * 但是在ASCII码里‘0’对应的刚好是48的二进制码，所以我们转换的时候只需要‘1’-‘0’=1；就可以了。
 * 而数字的ASCII码是按顺序规定的。所以其它字符要转换成数字都可以用减‘0’来表示。比如‘2’的ASCII是50，而我们要得到数字2，于是用‘2’-48=2了。
 */
class day22_1 {
public:
    string getHint(string secret, string guess) {
        int len = secret.length();
        int Anum = 0;
        vector<int> cntS(10), cntG(10);
        for (int i = 0; i < len; ++i) {
            if (secret[i] == guess[i]) ++Anum;
            else { 
                // s[i]-'a'就是让s[i]和a对应的ASCII码值相减
                ++cntS[secret[i] - '0'];
                ++cntG[guess[i] - '0'];
            }
        }
        // 由于多余的数字无法匹配，对于0 到 9 的每位数字，应取其在 secret 和 guess 中的出现次数的最小值
        int Bnum = 0;
        for (int j = 0; j < 10; j++) {
            Bnum += min(cntG[j], cntS[j]);
        }
        return to_string(Anum) + "A" + to_string(Bnum) + "B";
    }
};
/*
 * 844. 比较含退格的字符串
 * 栈 双指针 
 */
// 从后往前遍历，跳过被 '#' 删掉的字 看最后指向的是否相同
class day23_1 {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.length() - 1, j = T.length() - 1;
        int skipS = 0, skipT = 0;
        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (S[i] == '#') {
                    skipS++, i--;
                } else if (skipS > 0) {
                    skipS--, i--;
                } else {
                    break;
                }
            }
            while (j >= 0) {
                if (T[j] == '#') {
                    skipT++, j--;
                } else if (skipT > 0) {
                    skipT--, j--;
                } else {
                    break;
                }
            }
            if (i >= 0 && j >= 0) {
                if (S[i] != T[j]) {
                    return false;
                }
            } else {
                if (i >= 0 || j >= 0) {
                    return false;
                }
            }
            i--, j--;
        }
        return true;
    }
};

// 用栈来存结果 最后比较栈是否相同
class day23_2 {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> sres;
        stack<char> tres;
        for (auto& word : s) {
            if (word != '#') sres.push(word);
            else {
                if (!sres.empty()) sres.pop();
            }
        }
        for (auto& word : t) {
            if (word != '#') tres.push(word);
            else {
                if (!tres.empty()) tres.pop();
            }
        }
        return sres == tres;
    }
};
/*
 * 394. 字符串解码
 * 栈的输入输出 解码过程与栈天作之合
 */
class day24_1 {
public:
    string decodeString(string s) {
        string res = "";
        stack<int> nums;
        stack<string> strs;
        int num = 0;
        int len = s.length();
        for (int i = 0; i < len; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
            }
            else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
                res += s[i];
            }
            else if (s[i] == '[') {
                nums.push(num);
                num = 0;
                strs.push(res);
                res = "";
            }
            else if (s[i] == ']') {
                int times = nums.top();
                for (int j = 0; j < times; j++) {
                    strs.top() += res;
                }
                res = strs.top();
                strs.pop();
                nums.pop();
            }
        }
        return res;
    }
};
/*
 * 1046. 最后一块石头的重量
 * 
 */
class day25_1 {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() > 1) {
            sort(stones.begin(), stones.end());
            int a = stones.back();
            stones.pop_back();
            int b = stones.back();
            stones.pop_back();
            int sub = abs(b - a);
            stones.push_back(sub);
        }
        return stones[0];
    }
};
/*
 * 692. 前K个高频单词
 * 
 */
class day26_1 {
public:
bool static cmp(pair<string,int> &a,pair<string,int> &b) {   
    if(a.second == b.second) {
        int k = a.first.size() > b.first.size() ? b.first.size() : a.first.size();
        for(int i = 0;i < k; i++) {
            if(a.first[i] != b.first[i])
            return a.first[i] < b.first[i];  
        }
    }
    return a.second > b.second;
}
 // 哈希表的{key, value}结构 只能以key进行排序，若想以value进行排序 就要自己实现
 // 借用pair的巧妙结构，进行按照first or second 元素进行排序的方式
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> mp;
        for(int i = 0;i < words.size(); i++)
                mp[words[i]]++;
    vector<pair<string, int>> ans(mp.begin(), mp.end());

    sort(ans.begin(), ans.end(), cmp);
    ans.erase(ans.begin() + k, ans.end());
    vector<string> res;
    for(int i = 0; i < k; i++)
    res.push_back(ans[i].first);
    return res;
    }
};
