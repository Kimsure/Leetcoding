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
 * 69. x 的平方根 
 */
// 结果只保留整数部分
class Solution {
public:
    int mySqrt(long long x) {
        long long l = -1;
        long long r = x + 1;
        if (x == 0 || x == 1) return x;
        while (l + 1 != r) {
            long long mid = l + (r - l) / 2;
            long long sum = mid * mid;
            if (sum == x) return mid;
            if (sum > x) r = mid;
            else l = mid;
        } 
        return l;
    }
};
// 或者，这样写和保留小位的写法一致，控制eps即可
class Solution {
public:
    int mySqrt(long long x) {
        long long l = 0;
        long long r = x;
        if (x == 0 || x == 1) return x;
        const int eps = 1;
        while (r - l > eps) {
            long long mid = l + (r - l) / 2;
            long long sum = mid * mid;
            if (sum == x) return mid;
            if (sum > x) r = mid; // (mid >= sqrt(x))
            else l = mid;
        } 
        return l; // return l
    }
};
// 结果需要保留多少多少位小数部分
class Solution {
public:
    int mySqrt(double x) {
        double l = -100000;
        double r = 100000;
        // if (x == 0 || x == 1) return x;
        const double eps = 1e-6;
        while (r - l > eps) {
            double mid = l + (r - l) / 2;
            double sum = mid * mid;
            if (sum <= x) l = mid;
            else r = mid;
        } 
        return r; // return l
    }
};
/*
* 704. 二分查找
*/
// 蓝红
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int l = -1, r = len;
        while (l + 1 != r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) l = mid;
            else r = mid;
            
        }
        return -1;
        
    }
};
// Y总 整合 浮点数eps
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int l = -1;
        int r = len;
        const int eps = 1;
        while (r - l > eps) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) r = mid; 
            else l = mid;
        } 
        return -1;
    }
};
/*
 * 22. 括号生成
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
 */
class Solution {
public:
    vector<string> res;
    void dfs(int n, int left, int rigth, string str) {
        if (left == n && rigth == n) res.push_back(str);
        else {
            if (left < n) dfs(n, left + 1, rigth, str + "(");
            if (rigth < n && left > rigth) dfs(n, left, rigth + 1, str + ")");
        }
    }
    vector<string> generateParenthesis(int n) {
        dfs(n, 0, 0, "");
        return res;
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /* 定义一个新的链表用于存储求和的结果 */
        // cpp两种 结构体指针 的情况，可以思考一下
        struct ListNode listnew;
        ListNode* dummyHead = & listnew;
        // ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;
        /* 定义一个变量用于保存进位 */
        int carry = 0;

        /* 因为不知道l1和l2的长短所以只要有一个没有遍历完就继续遍历 遍历完的就不执行 */
        /* 
         * 第一次写while(l1 || l2)会错因为漏掉了最后一个进位《== 特别哟注意
        */
        while(l1 || l2 || carry){
            /* 只要不为空就继续求和 */
            if(l1 != NULL) carry += l1->val;
            if(l2 != NULL) carry += l2->val;
            /* 创建一个节点插入到新的链表并且值初始化为l1->val+l2->val的个位数 */
            ListNode* tmp = new ListNode(carry%10);
            /* 插入结点tmp因为是从头开始插入所以只需要每次更新cur */
            cur->next = tmp;
            cur = cur->next;
            /* 只要链表不为空就继续遍历下一个节点 */
            if(l1 != NULL) l1 = l1->next;
            if(l2 != NULL) l2 = l2->next;
            /* 获取上个节点的进位值 加到下个节点的运算中 */
            carry /= 10;
        }
        /* 注意这里不返回dummyHead因为这里相当于一个虚拟头节点 下一个才是正真的头节点 */
        return dummyHead->next;
    }
};
/*
 * 8. 字符串转换整数 (atoi)
 */
class Solution1 {
public:
    int myAtoi(string s) {
        long long res = 0;
        int cur = 0;
        int flag = 1; // 正负号

        while(s[cur] == ' ' && cur < s.length()) cur++;
        if (cur < s.length() && s[cur] ==  '+') ++cur;
        else if (cur < s.length() && s[cur] ==  '-') {
            ++cur;
            flag = -1;
        }
        // 判断了开头的空格与正负号，开始读取数字
        while(cur < s.length() && s[cur] <= '9' && s[cur] >= '0') {
            int num = s[cur] - '0'; // -'0'正好是对应的int数
            num = num * flag;
            res = res * 10 + num; // 进位
            if (res <= -2147483648) return -2147483648;
            else if (res >= 2147483647) return 2147483647;
            cur++;
        }
        return res;
    }
};
class Solution2 {
public:
    int myAtoi(string s) {
        int res = 0;
        int cur = 0;
        int flag = 1; // 正负号

        while(s[cur] == ' ' && cur < s.length()) ++cur;
        if (cur < s.length() && s[cur] ==  '+') ++cur;
        else if (cur < s.length() && s[cur] ==  '-') {
            ++cur;
            flag = -1;
        }
        // 判断了开头的空格与正负号，开始读取数字
        while(cur < s.length() && s[cur] <= '9' && s[cur] >= '0') {
            int num=s[cur]-'0';
            //判断是否溢出
            //⭐️⭐️⭐️「注意理解，这里是核心位置代码」
            //学习这种判断溢出的方法
            if( res > INT_MAX/10 || (res == INT_MAX/10 && num > INT_MAX % 10 ) ) {
                return flag == 1 ? INT_MAX : INT_MIN;    
            }
            res =  res*10 + num;
            ++cur;

        }
        return flag == 1 ? res : -res;
    }
};
/*
 * 41. 缺失的第一个正数
 * 考虑清楚什么是原地哈希，为什么这道题原地哈希函数为 f(num[i]) = nums[i] - 1 (nums[i] = i + 1), 如果是其它题目原地哈希函数为什么？缺失的第二个正数怎么做？
 */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i + 1) {
                if (nums[i] <= 0 || nums[i] > nums.size() || nums[i] == nums[nums[i] - 1]) break;
                int idx = nums[i] - 1;
                nums[i] = nums[idx];
                nums[idx] = idx + 1;
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != (i + 1)) {
                return (i + 1);
            }
        }
        return nums.size() + 1;
    }
};
/*
 * 堆排序合集（优先队列，topK问题）
 */
/*
 * 347. 前 K 个高频元素
 */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
    //1.map记录元素出现的次数
        unordered_map<int,int>map;//两个int分别是元素和出现的次数
        for(auto& c:nums){
            map[c]++;
        }
    //2.利用优先队列，将出现次数排序
        //自定义优先队列的比较方式，小顶堆
        struct myComparison{
            bool operator()(pair<int,int>&p1,pair<int,int>&p2){
                return p1.second>p2.second;//小顶堆是大于号
            }
        };
        //创建优先队列
        priority_queue<pair<int,int>,vector<pair<int,int>>,myComparison> q;
        //遍历map中的元素
        //1.管他是啥，先入队列，队列会自己排序将他放在合适的位置
        //2.若队列元素个数超过k，则将队顶元素出队（队顶元素一定是最小的那个，后进先出）
        for(auto& a:map){
            q.push(a);
            if(q.size()>k){
               q.pop(); 
            }
        }
        vector<int>res;
        while(!q.empty()){
            res.emplace_back(q.top().first);
            q.pop();
        }
        return res;
    }
};
/*
 * 面试题 17.14. 最小K个数
 */
class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        struct mycmp {
            bool operator () (int &a, int &b) {
                return a < b;
            }
        };
        // 比较int型可以直接less，不用重载cmp函数
        priority_queue <int, vector<int>, mycmp> q; // 生成大顶堆(mycmp == less)
        for (int i = 0; i < arr.size(); i++) {
            q.push(arr[i]);
            if (q.size() > k) q.pop();
        }
        vector<int> res;
        while (!q.empty()) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};
/*
 * 692. 前K个高频单词
 */
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnt;
        for (auto& word : words) {
            cnt[word]++;
        }
        // 三元比较符，先比较出现次数(.second)，再比较字典序(.first)
        struct mycmp {
            bool operator () (const pair<string, int>& a, const pair<string, int>& b) {
                return a.second == b.second ? a.first < b.first : a.second > b.second;
            }
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, mycmp> q;
        for (auto& it : cnt) {
            q.emplace(it);
            if (q.size() > k) {
                q.pop();
            }
        }
        vector<string> ret(k);
        // 注意这的顺序，因为是队列，这里按正常顺序top出来的是较小的值，所以要逆序push进vector
        // 其实也可以用while循环+push vector做，和上面的一样
        for (int i = k - 1; i >= 0; i--) {
            ret[i] = q.top().first;
            q.pop();
        }
        return ret;
    }
};
/*
 * 二叉树合集
 */
/*
 * 129. 求根节点到叶节点数字之和（递归）
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    int dfs(TreeNode* node, int persum) {
        if (node == nullptr) return 0;
        int sum = persum*10 + node->val;
        if (node->left == nullptr && node->right == nullptr) return sum;
        else return dfs(node->left, sum) + dfs(node->right, sum);
    }
    int sumNumbers(TreeNode* root) {
        int sum = dfs(root, 0);
        return sum;
    }
};
/*
 * 543. 二叉树的直径（递归）
 */
class Solution {
   int maxlen;
private:
    int dfs(TreeNode* root) { 
        if (root == nullptr) return 0;
        int leftSize = dfs(root->left);
        int rightSize = dfs(root->right);
        maxlen = max(maxlen, leftSize + rightSize + 1);
        return max(leftSize, rightSize) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxlen = 1;
        dfs(root);
        return maxlen - 1;
    }
};
/*
 * 递归 回溯合集（子集, 组合篇）
 */
/*
 * 78. 子集
 */
class Solution {
public:
    vector<vector<int>> res;
    void backtrack(vector<int> nums, vector<int>& path, int start)
    {
        res.push_back(path);
        for(int i = start; i < nums.size(); i++)
        {
            path.push_back(nums[i]);//做出选择
            backtrack(nums, path, i+1);//递归进入下一层，注意i+1，标识下一个选择列表的开始位置，最重要的一步
            path.pop_back();//撤销选择
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        backtrack(nums, path, 0);
        return res;
    }
};
/*
 * 90. 子集 II(去重)
 */
// 应该去除当前选择列表中，与上一个数重复的那个数，引出的分支，如 “2，2” 这个选择列表，第二个 “2” 是最后重复的，应该去除这个 “2” 引出的分支
class Solution {
public:
    vector<vector<int>> res;
    void backtrack(vector<int> nums, vector<int>& path, int start)
    {
        res.push_back(path); // 把子集的空集先加进去
        for(int i = start; i < nums.size(); i++)
        {
            //剪枝去重
            if(i > start && nums[i] == nums[i - 1]) continue;
            path.push_back(nums[i]);//做出选择
            backtrack(nums, path, i+1);//递归进入下一层，注意i+1，标识下一个选择列表的开始位置，最重要的一步
            path.pop_back();//撤销选择
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int> path;
        backtrack(nums, path, 0);
        return res;
    }
};
/*
 * 90. 组合问题
 */
// 没有组合数量要求，仅仅是总和的限制，所以递归没有层数的限制
//* 可以思考一下，这里如果排序后再递归组合问题，continue能换成break，因为前面小，小的组合不了，后面更不行
class Solution {
public:
    vector<vector<int>> res;
    void backtrack(vector<int>& candidates, vector<int>& path, int sum, int target, int start) {
        if (sum == target) res.push_back(path); // 结束条件
        for (int i = start; i < candidates.size(); i++) {
            if (sum > target) continue;
            path.push_back(candidates[i]);
            backtrack(candidates, path, sum + candidates[i], target, i); // 组合问题start可以重复，不用i+1了，表示可以重复读取当前的数
            path.pop_back(); // 回溯
        }
        // * 或者如下方法
        for (int i = start; i < candidates.size(); i++) {
            sum += candidates[i]; // 把sum写在外面，回溯时自然也要和path一样撤回
            if (sum > target) continue;
            path.push_back(candidates[i]);
            // backtrack(candidates, path, sum + candidates[i], target, i); // 组合问题start可以重复，不用i+1了，表示可以重复读取当前的数
            backtrack(candidates, path, sum, target, i); // 组合问题start可以重复，不用i+1了，表示可以重复读取当前的数
            sum -= candidates[i]; // 回溯
            path.pop_back(); // 回溯
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> path;
        backtrack(candidates, path, 0, target, 0);
        return res;
    }
};
/*
 * 递归 回溯合集（排列篇）
 */
/*
 * 全排列
 */
class Solution {
public:
    vector<int> path;
    vector<vector<int>> res;
    void backtrack(vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) { //从给定的数中除去，用过的数，就是当前的选择列表
            if (used[i] == true) continue; //用过的就跳过
            used[i] = true; // 没用过的加进来 然后设为用过了
            path.push_back(nums[i]);
            backtrack(nums, used); // 递归
            path.pop_back(); // 回溯
            used[i] = false; // used回溯
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false); //used初始化为false
        backtrack(nums, used);
        return res;
    }
};
/*
 * 全排列 II（去重）
 */
// 重复序列nums返回不重复的全排列 必定去重 树层去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking (vector<int>& nums, vector<bool>& used) {
        // 此时说明找到了一组
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
            // used[i - 1] == false，说明同一树层nums[i - 1]使用过
            // 如果同一树层nums[i - 1]使用过则直接跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true; //设置当前数已用
                path.push_back(nums[i]); 
                backtracking(nums, used); // 递归 下一层
                path.pop_back(); // 回溯
                used[i] = false; // 撤销回溯
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end()); // 不重复的问题，需要剪枝的 都要排序
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
/*
 * 剑指 Offer 38. 字符串的排列
 */
class Solution {
private:
    vector<string> result;
    string path;
    void backtracking (const string& s, vector<bool>& used) {
        // 此时说明找到了一组
        if (path.size() == s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
            // used[i - 1] == false，说明同一树层nums[i - 1]使用过
            // 如果同一树层nums[i - 1]使用过则直接跳过
            if (i > 0 && s[i] == s[i - 1] && used[i - 1] == false) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true; //设置当前数已用
                path.push_back(s[i]); 
                backtracking(s, used); // 递归 下一层
                path.pop_back(); // 回溯
                used[i] = false; // 撤销回溯
            }
        }
    }
public:
    vector<string> permutation(string s) {
        if (s.size() == 0) return result;
        sort(s.begin(), s.end()); // 不重复的问题，需要剪枝的 都要排序
        vector<bool> used(s.size(), false);
        backtracking(s, used);
        return result;
    }
};
/*
 * 165. 比较版本号
 */
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0;
        int j = 0;
        while (i < version1.size() || j < version2.size()) {
            long long num1 = 0, num2 = 0;
            while (i < version1.size() && version1[i] != '.') {
                num1 = num1*10 + version1[i] - '0'; // 实现stoi, 进行
                i++;
            }
            while (j < version2.size() && version2[j] != '.') {
                num2 = num2*10 + version2[j] - '0';
                j++;
            }
            if (num1 > num2) return 1;
            else if (num1 < num2) return -1;
            i++;
            j++; // 开始下一个 '.' 之后的版本判断
        }
        return 0;
    }
};
/*
 *  113. 路径总和II
 */
/*
 * 这种做法递归的时候会出错，注意分析一下，递归树的时候的判断结束条件要到 node = nullptr？ 这一步
 * 递归不能到 node -> left == nullptr && node -> right == nullptr 这一步，此时递归是错的，分析一下
 * 原因在于
 */

/*
class Solution {
private:
    int count = 0;
    vector<int> ans;
    vector<vector<int>> res;
    void DFS(TreeNode* cur, int count) {
        ans.push_back(cur->val);
        // cout << cur->val << endl;
        if (cur -> left == nullptr && cur -> right == nullptr) {
            if (count == 0) res.push_back(ans);
            // cout << ans.back() << endl;
            return;
        }
        DFS(cur->left, count - cur->left->val);
        DFS(cur->right, count - cur->right->val);
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return res;
        DFS(root, targetSum - root->val);
        return res;
    }
};
*/