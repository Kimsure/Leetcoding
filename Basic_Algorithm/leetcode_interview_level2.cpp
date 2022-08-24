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
 * 202. 快乐数
 */
// 哈希set 这里分析了 集合不会过大
class day1_0{
    public:
    //取数值每个位上的平方和
    int getSum(int n){
        int sum = 0;
        while(n) {
            int bit = n % 10;
            sum = sum + bit * bit;
            n = n / 10;
        }
        return sum;
    }
    bool isHappy(int n){
        unordered_set<int> set;
        while(1){
            int sum = getSum(n);
            if (sum == 1){
                return true;
            }
             // 如果这个sum曾经出现过，说明已经陷入了无限循环了，立刻return false
            if (set.find(sum) != set.end()){
                return false;
            }
            else{
                set.insert(sum);
            }
            n = sum;
        }   
    }
};
// 快慢指针 抽象成带环链表的样子
class day1_2 {
public:
    int bitSquareSum(int n) {
        int sum = 0;
        while(n > 0)
        {
            int bit = n % 10;
            sum += bit * bit;
            n = n / 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n, fast = n;
        do{
            slow = bitSquareSum(slow);
            fast = bitSquareSum(fast);
            fast = bitSquareSum(fast);
        }while(slow != fast);
        
        return slow == 1;
    }
};
/*
 * 54. 螺旋矩阵
 */
// BFS模拟 旋转方向
class day2_1 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 开辟了新的布尔矩阵 空间复杂度不是O(1)
        vector<int> res;
        if (matrix.empty()) return res;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<bool>> st(n, vector<bool>(m, false)); // 布尔矩阵判断当前位置是否已经走过
        int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; // 四个方向，矩阵上下为x方向(下正上负)，左右为y方向(右正左负)
        int x = 0, y = 0, d = 1; // d是初始方向判断，可以为0，1，2，3，根据顺时针来看初始方向是向右，所以d是1
        for (int k = 0; k < n * m; k ++ )
        {
            res.push_back(matrix[x][y]);// x,y是矩阵元素下标
            st[x][y] = true;

            int a = x + dx[d], b = y + dy[d];
            // 这个 if 判断是否到边界或者是否到已经走过的区域
            if (a < 0 || a >= n || b < 0 || b >= m || st[a][b])
            {
                // 取余操作使得d向后移一位，即改变方向
                d = (d + 1) % 4;
                a = x + dx[d], b = y + dy[d];
            }
            x = a, y = b;
        }
        return res;
    }
};
// 按层模拟 不需要额外空间来表示是否遍历过。控制层数增减来缩小遍历范围
class day2_2 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int left = 0;
        int right = matrix[0].size() - 1;
        int top = 0;
        int bottom = matrix.size() - 1;
        int num = (right + 1) * (bottom + 1);
        while (num > 0)
        {
            // 左上到右上 
            for (int i = left; i <= right && num > 0; i++) {
                res.push_back(matrix[top][i]);
                num--;
            }
            top++; // 第一行遍历完，少一行，top向下移动
            // 右上到右下
            for (int i = top; i <= bottom && num > 0; i++) {
                res.push_back(matrix[i][right]);
                num--;
            }
            right--; // 最右一列遍历完 少一列，right向左移动
            for (int i = right; i >= left && num > 0; i--) {
                res.push_back(matrix[bottom][i]);
                num--;
            }
            bottom--; // 最下面一行遍历完，少一行，bottom向上移动
            for (int i = bottom; i >= top && num > 0; i--) {
                res.push_back(matrix[i][left]);
                num--;
            }
            left++; // 最左面一列遍历完，少一列，left向左移动
        }
        return res;

    }
};
/*
 * 1706. 球会落何处
 */
class day3_1 {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(); // 箱子的行数 列数
        vector<int > res;
        for (int i = 0; i < n; i++) { // 每个球
            int loc = i; // 球的初始位置 即在哪一列
            for (int j = 0; j < m; j++) { // 从第一行往下落 分别求出球掉到每层的位置
                int dir = grid[j][loc]; // 方向，下降过程中向左或向右下降
                loc += dir; // 更新球在下一层的纵坐标,向右移动(纵坐标加1)/向左移动(纵坐标减1)
                if (loc < 0 || loc > n || grid[j][loc] == -dir) {// 不能超出范围, 且下一层位置与上一层不形成夹角
                    loc = -1;//当形成夹角或被挡在箱子侧边时,球将会卡在盒子里,所以该球下降的结果值直接赋值为-1;
                    break;
                }
            }
            res[i] = loc; // 存储
        }
        return res;
    }
};
/*
 * 14. 最长公共前缀
 */
class day4_1 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        /* vector<string> 的 vector 形式比较特殊, 类似于vector<vector<int>> 形式，string自己又是个小数组 */
        // for (auto i = strs.begin(); i != strs.end(); i++) {
        //     cout << *i << ' ';
        // }
        // for (int i = 0; i < strs.size(); i++) {
        //     cout << strs[i][0] << ' ';
        // }
        if (strs.size() < 1) return "";
        for (int i = 0; i < strs[0].size(); i++) {
            char a = strs[0][i]; // 第一个str的第一个char
            for (int j = 1; j < strs.size(); j++) { // 从第二个str开始比
                if (strs[j][i] != a || i == strs[j].size()) return strs[0].substr(0, i);
            }
        }
        return strs[0];
    }
};
/*
 * 43. 字符串相乘
 */
class day5_1 {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        string ans = "0";
        int m = num1.size(), n = num2.size();
        for (int i = n - 1; i >= 0; i--) {
            string curr;
            int add = 0;
            for (int j = n - 1; j > i; j--) {
                curr.push_back(0);
            }
            int y = num2.at(i) - '0';
            for (int j = m - 1; j >= 0; j--) {
                int x = num1.at(j) - '0';
                int product = x * y + add;
                curr.push_back(product % 10);
                add = product / 10;
            }
            while (add != 0) {
                curr.push_back(add % 10);
                add /= 10;
            }
            reverse(curr.begin(), curr.end());
            for (auto &c : curr) {
                c += '0';
            }
            ans = addStrings(ans, curr);
        }
        return ans;
    }

    string addStrings(string &num1, string &num2) {
        int i = num1.size() - 1, j = num2.size() - 1, add = 0;
        string ans;
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1.at(i) - '0' : 0;
            int y = j >= 0 ? num2.at(j) - '0' : 0;
            int result = x + y + add;
            ans.push_back(result % 10);
            add = result / 10;
            i--;
            j--;
        }
        reverse(ans.begin(), ans.end());
        for (auto &c: ans) {
            c += '0';
        }
        return ans;
    }
};
/*
 * 19. 删除链表的倒数第 N 个结点
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// 神仙的递归 但是可能产生野指针的情况
class day6_1 {
public:
    int cur = 0;
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head) {
            head->next = removeNthFromEnd(head->next, n);
            cur++;
            if (cur == n) return head->next;
            return head;
        }
        else return nullptr;
    }
};
// 快慢指针
class day6_2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow = head;
        ListNode* fast = head;
        if (!head || !head->next) return nullptr;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        if (!fast) return head->next;
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};
/*
 * 234. 回文链表
 */
class day7_1 {
public:
//快指针走到末尾，慢指针刚好到中间。其中慢指针将前半部分反转。然后比较。
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* cur = nullptr;
        while (fast && fast->next) {
            //快慢指针一起走，快指针走两步，慢指针走一步
            //反转慢指针走的链表，当快指针走到末尾，慢指针就走到中间
            fast = fast->next->next;
            //其实就是反转前一部分链表
            ListNode* tmp = slow->next;
            slow->next = cur;
            cur = slow;
            slow = tmp;
        }
        // 两种情况 一：链表长度n为奇数时，此时fast不为null，而是最后一个节 点，slow指向（（n-1）/2，
        // 二：链表长度n为偶数，此时fast为null，slow正好指向后半部分的起始位置， 所以不用移动
        if (fast) slow = slow->next; // 当链表长度为奇数时，将slow移动到后半段的开始处
        while(slow) {
            if (slow->val != cur->val) return false;
            else {
                slow = slow->next;
                cur = cur->next;
            }
        }
        return true;
    }
};
/*
 * 328. 奇偶链表
 */
class day8_1 {
public:
    ListNode* oddEvenList(ListNode* head) {
        // 特殊情况
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* ohead = head; // head奇数节点头，ohead奇数节点尾
        ListNode* ehead = head->next;  // ehead偶数节点头，
        ListNode* fehead = head->next; // fehead偶数节点尾
        while (ohead->next != nullptr && fehead->next) {
            ohead->next = fehead->next;
            ohead = ohead->next;
            fehead->next = ohead->next;
            fehead = fehead->next;
        }
        ohead->next = ehead;
        return head;
    }
};
/*
 * 148. 排序链表
 */
class day9_1 {
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummy = new ListNode();
        ListNode* pre = dummy;
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->val <= head2->val) {
                pre->next = head1;
                head1 = head1->next;
            } else {
                pre->next = head2;
                head2 = head2->next;
            }
            pre = pre->next;
        }
        pre->next = head1 != nullptr ? head1 : head2;
        return dummy->next;
    }
    ListNode* findMid(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);
        ListNode *slow = dummy, *fast = dummy;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == nullptr) {
            return head;
        }
        ListNode* mid = findMid(head);
        ListNode* head2 = mid->next;
        mid->next = nullptr;
        ListNode* left = sortList(head);
        ListNode* right = sortList(head2);
        return merge(left, right);
    }
};
/*
 * 2131. 连接两字母单词得到的最长回文串
 * 首先需要对出现的字符串进行统计其出现的次数，那么开始分情况讨论：
 * 形如 “ab” 的字符串，只有找到 “ba” 才可以放入答案中进行统计，两者出现次数的最小值即可计入答案 aa 中。
 * 为什么？因为我们可以往答案字符串的两端各放一个进行叠加即可。
 *     ab xxxxxxx ba像这样
 *     形如 “aa” “bb” 的字符串，可以根据它们出现的次数分为奇数个和偶数个讨论：
 *     偶 + 偶 = 偶，很显然，直接统计入答案 bb 中即可；
 *     aa bb bb aa / bb aa aa bb 喜欢咋放就咋放~
 *     偶 + 奇 = 奇，没问题，可以交叉着放，直接统计入答案 bb 中即可，但是得出来的序列出现次数变成了一个奇数；
 *     aa bb aa bb aa
 *     奇 + 奇 = 偶，这样就不合法了，例如aa bb aa aa，不存在一种正确的姿势构成回文串，
 *     也就是最终的回文串中不能够同时存在两种出现奇数次的形如 “aa” 字符串。
 * 那么，我们可以知道，只能够最多存在一种出现次数为奇数次的形如 “aa” 的字符串，
 * 所以需要对他们出现的次数进行减1来使他们出现的次数变成偶数。我们可以直接统计奇数次出现的次数，记为cc，最后减去c-1c−1即可。
 */
class day10_1 {
public:
    int longestPalindrome(vector<string>& words) {
        // a: 统计 形如 “ab”
        // b：统计 所有 形如 “aa” 出现的次数（包括 奇数次 和 偶数次）
        // c：统计 奇数次 “aa” 出现的个数
        int a = 0, b = 0, c = 0;
        unordered_map<string, int> ct;
        for(int i = 0; i < words.size(); ++i) ct[words[i]]++;
        for(auto it: ct)
        {
            if(it.first[0] == it.first[1]){
                if(it.second & 1){
                    c++;
                }
                b += it.second;
            }
            else {
                string to = "";
                to += it.first[1];
                to += it.first[0];
                if(ct.count(to)){
                    //对于“ab” 可以删除 “ba”减少遍历次数，但是要乘2
                    a += 2 * min(ct[to], it.second);
                    ct.erase(to);
                }
            }
        }
        return 2 * (b + a - (c <= 1 ? 0 : c - 1));
    }
};
/*
 * 621. 任务调度器
 */
class day11_1 {
private:
    static bool cmp(pair<char, int> a, pair<char, int> b) {
        return a.second > b.second;
    }
public:
    int leastInterval(vector<char>& tasks, int n) {
        int len = tasks.size();
        // 特殊用例
        if (n == 0 || len == 1) return len;
        // 哈希表统计不同task字符出现次数
        unordered_map<char, int> hash;
        for (auto word : tasks) hash[word]++;
        // 利用vector pair 来进行基于value的排序
        vector<pair<char, int>> vec(hash.begin(), hash.end());
        sort(vec.begin(), vec.end(), cmp);
        int count = 0; // count是有几种 出现次数为最大值的
        int maxnum = 0;
        // 找出最多的出现次数
        for (auto v : vec) {
            if (v.second > maxnum) {
                maxnum = v.second;
                count = 1;
            }
            else if (v.second == maxnum) count++;
        }
        // (maxnum - 1)是出现次数 * (n + 1)是前maxnum-1次需要多少时间
        // max函数是防止算出来比原数组短，那是不可能的情况，最小也是原数组长度
        return max(len, (maxnum - 1) * (n + 1) + count);
    }
};
/*
 * 226. 翻转二叉树
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class day12_1 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
/*
 * 110. 平衡二叉树
 * Definition for a binary tree node.
 */
class day13_1 {
public:
    int getHeight(TreeNode* node) {
        if (node == NULL) return 0;
        int leftHeight = getHeight(node -> left);
        if (leftHeight == -1) return -1;
        int rightHeight = getHeight(node -> right);
        if (rightHeight == -1) return -1;
        return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);

    }
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};
/*
 * 543. 二叉树的直径
 */
class Solution {
    int maxlen;
private:
    int dfs(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr) return 0;
        int leftSize = dfs(root->left);
        int rightSize = dfs(root->right);
        maxlen = max(maxlen, leftSize + rightSize);
        return max(leftSize, rightSize) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxlen = 1;
        if (root == nullptr) return 0;
        dfs(root);
        return maxlen;
    }
};
/*
 * 437. 路径总和III
 * 递归套递归，太优雅了
 */
class Solution6_X {
private:
    int rootSum(TreeNode* root, long long targetSum) {
        if (root == nullptr) return 0;
        long long ret = 0;
        if (root->val == targetSum) ret++;
        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }
public:
    int pathSum(TreeNode* root, long long targetSum) {
        if (root == nullptr) return 0;
        int ans;
        ans = rootSum(root, targetSum);
        ans += pathSum(root->left, targetSum); // 左子节点当作下一次递归的父节点
        ans += pathSum(root->right, targetSum); // 右子节点当作下一次递归的父节点
        return ans;
    }
};
/*
 * 74. 搜索二维矩阵
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size(); // m 是有多少行 n 是有多少列
        if (target > matrix[m - 1][n - 1]) return false;
        int l = -1, r = m*n; // 善用除法和区域，来得到横坐标和纵坐标
        while (l + 1 != r) {
            int mid = l + (r - l) / 2;
            // 用总块数 / 列数 == 在哪一行； % 列数 == 在哪一列
            int i = mid / n;
            int j = mid % n;
            if (matrix[i][j] > target) {
                r = mid;
            }
            else if (matrix[i][j] < target) {
                l = mid;
            }
            else if (matrix[i][j] == target) return true;
        }
        return false;
    }
};
/*
 * 33. 搜索旋转排序数组
 * 先二分找到两个升序的子数组 然后再分别二分找数值
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = -1, n = nums.size(), r = n;
        while (l + 1 != r) {
            int mid = l + r >> 1;
            if (nums[mid] == target) return mid;
            // 此时 [mid, n - 1] 有序
            if (nums[0] > nums[mid]) {
                if (target > nums[mid] && target <= nums[n - 1]) l = mid;
                else r = mid;
            }
            else if(nums[0] <= nums[mid]) {  // [0,mid-1)有序
                // 二分查找
                if(nums[0] <= target && target < nums[mid]) r = mid;
                else l = mid;
            }
        }
        return -1;
    }
};
/*
 * 108. 将有序数组转换为二叉搜索树
 * BST的中序遍历是递增的（左中右）。那么将数组从中间值分开，那么小的都是左子树，大的都是右子树，左右又可以二分找往下的子树
 */
class Solution {
private:
    TreeNode* BSTDFS(vector<int>& nums, int l, int r) {
        if (l > r) return nullptr;
        int mid = l + r >> 1;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = BSTDFS(nums, l, mid - 1);
        node->right = BSTDFS(nums, mid + 1, r);
        return node;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        TreeNode* node =  BSTDFS(nums, l, r);
        return node;
    }
};
/*
 * 230. 二叉搜索树中第K小的元素
 * 
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left; // 左
            }
            root = stk.top();
            stk.pop();
            --k; // 找到最小的了
            if (k == 0) break; // 直接结束
            root = root->right; // 开始右边
        }
        return root->val; // 返回k==0时的节点对应值
        // 因为左中右中序遍历就是递增的 每次--k就是找前第k个节点值
    }
};
/*
 * 173. 二叉搜索树迭代器
 * 等价于对二叉搜索树进行中序遍历
 */
// 直接进行二叉树中序遍历，整个过程分到next and hasnext里
class BSTIterator {
private:
    stack<TreeNode*> stk;
    TreeNode* cur;
public:
    BSTIterator(TreeNode* root) {
        cout << "BSTIterator created" << endl;
        cur = root;
    } // 构造函数
    
    int next() {
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        int res = cur->val;
        cur = cur->right;
        return res;
    }
    
    bool hasNext() {
        return !stk.empty() || cur != nullptr;
    }
};
// 将二叉树中序遍历结果存到数组里，然后数组作为迭代器
class BSTIterator {
private:
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
public:
    vector<int> vec;
    int idx = 0;
    BSTIterator(TreeNode* root) {
        cout << "BSTIterator created" << endl;
        inorder(root, vec);
    }
    int next() {
        return vec[idx++];
    }
    bool hasNext() {
        return idx < vec.size();
    }
};
/*
 * 994. 腐烂的橘子
 * 
 */
// 每分钟，腐烂的橘子 周围 4 个方向上相邻的新鲜橘子都会腐烂
// 所以必然是BFS 每遍历一层 记一次 最后统计总次数
class Solution {

        int dirt[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
public:
    int orangesRotting(vector<vector<int>>& grid) {
            int min = 0,fresh = 0;///fresh记录每一个新鲜的水果,min为记录层数
            //队列，保存一对坐标
            queue<pair<int,int>>que;
            //遍历地图
            for(int i = 0;i<grid.size();i++){
                for(int j = 0;j<grid[0].size();j++){
                    if(grid[i][j]==1)fresh++;   //记录新鲜水果的数量
                    else if (grid[i][j] ==2) que.push({i,j});//记录腐烂水果坐标
                }
            }
            //层序遍历，while（直到没有元素）
            //保存对首元素，
            //遍历层的元素
            //遍历层的四周元素
            //如果符合就标记走过，添加到新的队列，并且水果新鲜-1
        while(!que.empty()){
            int n = que.size();
            bool rotten = false;
            //遍历队列一层的元素
            for(int i= 0;i<n;i++){
                auto x = que.front();   //保存腐烂元素的坐标
                que.pop();      //出队列
                for(auto cur: dirt){
                    int i = x.first + cur[0];   //更新x的坐标
                    int j = x.second + cur[1];  //更新y的坐标
                    //如果遍历的坐标是新鲜的和符合要求的
                    if(i>=0 && i<grid.size()&&j>=0&&j<grid[0].size()&&grid[i][j]==1){
                        grid[i][j] = 2;     //更新坐标
                        que.push({i,j});    //加入队列
                        fresh--;            //新鲜数量减一
                        rotten = true;      //标记遍历完一层
                    }
                }
            }
            if(rotten) min++; //遍历完一层，记录+1
        }
        return fresh ? -1:min; //如果fresh为0，全完腐烂，返回min
                                //如果fresh不为0，表示还有新鲜的，返回-1
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
 * 199. 二叉树的右视图
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root) que.push(root);
        while (!que.empty())
        {   
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == size - 1) res.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return res;
    }
};
/*
 * 232. 用栈实现队列
 */
class MyQueue {
private:
    stack<int> stk1;
    stack<int> stk2;
public:
    MyQueue() {
        cout << "stack for queue" << endl;  
    }
    
    void push(int x) {
        stk1.push(x);
    }
    
    int pop() {
        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        int ans = stk2.top();
        stk2.pop();
        return ans;
    }
    
    int peek() {
        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        return stk2.top();
    }
    
    bool empty() {
        if (stk1.empty() && stk2.empty()) return true;
        return false;
    }
};
/*
 * 155. 最小栈，设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈
 */
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};
/*
 * 208. 实现Trie前缀树
 */
class Trie {
private:
    bool isEnd;
    Trie* next[26];
public:
    Trie() {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->next[c-'a'] == NULL) {
                node->next[c-'a'] = new Trie();
            }
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            node = node->next[c - 'a'];
            if (node == NULL) {
                return false;
            }
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            node = node->next[c-'a'];
            if (node == NULL) {
                return false;
            }
        }
        return true;
    }
};
/*
 * 56. 合并区间
 */
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //这里数组需要有序的
        sort(intervals.begin(), intervals.end());
        vector<vector<int>>ans;
        int j = 0;
        //这里需要注意一下，不需要i++
        for(int i = 0;i<intervals.size();){
            //将数组的最后一个数值赋值给临时变量temp
            int temp = intervals[i][1];
            //j往后比i多一位，指向后面的数组
            j = i + 1;
            //如果没有溢出，并且后面的数组的第一位大于前面数组的最后一位,有重合
            while(j < intervals.size() && intervals[j][0] <= temp)
            {
                //去第二个数组和第一个数组的第二个数值的最大值
                temp = max(temp, intervals[j][1]);
                j++;//j指向下一个数组
            }
            ans.push_back({intervals[i][0], temp});
            i = j; //将j的指针赋值给i
        }
        //遍历结束后，返回ans
        return ans;
    }
};
/*
 * 57. 插入区间
 */
// 代码随想录 三个while
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int index = 0; // intervals的索引
        // cout << intervals[index][1] << " " << newInterval[0] << endl;
        // 步骤一：找到需要合并的区间
        while (index < intervals.size() && intervals[index][1] < newInterval[0]) {
            result.push_back(intervals[index++]);
        }
        // 步骤二：合并区间
        while (index < intervals.size() && intervals[index][0] <= newInterval[1]) {
            newInterval[0] = min(intervals[index][0], newInterval[0]);
            newInterval[1] = max(intervals[index][1], newInterval[1]);
            index++;
        }
        result.push_back(newInterval);
        // 步骤三：处理合并区间之后的区间
        while (index < intervals.size()) {
            result.push_back(intervals[index++]);
        }
        return result;
    }
};
// 在56的基础上做，插入新区间然后排序，就是合并区间的问题
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval); // 插入新区间
        //这里数组需要有序的
        sort(intervals.begin(), intervals.end());
        vector<vector<int>>ans;
        int j = 0;
        //这里需要注意一下，不需要i++
        for(int i = 0;i<intervals.size();){
            //将数组的最后一个数值赋值给临时变量temp
            int temp = intervals[i][1];
            //j往后比i多一位，指向后面的数组
            j = i + 1;
            //如果没有溢出，并且后面的数组的第一位大于前面数组的最后一位,有重合
            while(j < intervals.size() && intervals[j][0] <= temp)
            {
                //去第二个数组和第一个数组的第二个数值的最大值
                temp = max(temp, intervals[j][1]);
                j++;//j指向下一个数组
            }
            ans.push_back({intervals[i][0], temp});
            i = j; //将j的指针赋值给i
        }
        //遍历结束后，返回ans
        return ans;
    }
};
/*
 * 行星碰撞
 */
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
       
        stack<int>st;
        vector<int>res;
       for(int& asteroid:asteroids ){
           //栈为空，则栈加入一个元素
           if(st.empty()) {
               st.push(asteroid);
               continue;
           }
           int top =st.top();

           if(top>0&&asteroid>0) st.push(asteroid);//大于0 直接入栈

           else if(top<0&&asteroid<0) st.push(asteroid);//都小0 直接入栈

           else if(top<0&&asteroid>0)  st.push(asteroid); //栈顶小于0，asteroid大于0
           
           else if(top>0&&asteroid<0) { //栈顶元素大于0，asteroid<0


                // 1,2,-1, 直接continue
                if(abs(asteroid)<top) continue; 
                //1,4,3,-4
                while(!st.empty()&&st.top()>0&&abs(asteroid)>st.top()){
                    st.pop(); // 1,4
                }
                if(!st.empty()&&abs(asteroid)==st.top()) {
                    st.pop(); // 1 对冲抵消后asteroid就不存在了
                    continue;
                }
                // [-2,-2,1,-2] 经过上面后变成[-2,-2]
                if(!st.empty()&&st.top()<0)  st.push(asteroid);
                //[1,-2,-2,-2] 
                if(st.empty())st.push(asteroid);        
            } 
       }
       while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
    
};
/*
 * 基本计算器
 */
class Solution {
public:
    int calculate(string s) {
        char op = '+';
        int i = 0;
        long left = 0, right = 0;
        while (i < s.length()) {
            if (s[i] != ' ') {
                long n = 0;
                while (i < s.length() && isdigit(s[i])) {
                    n = 10 * n + (s[i++] - '0');
                }
                switch (op) {
                    case '+' : left += right; right = n; break;
                    case '-' : left += right; right = -n; break;
                    case '*' : right *= n; break;
                    case '/' : right /= n; break;
                }
                if (i < s.length()) {
                    op = s[i];
                }
            }
            ++i;
        }
        return left + right;
    }
};