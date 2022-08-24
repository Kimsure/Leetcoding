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

 