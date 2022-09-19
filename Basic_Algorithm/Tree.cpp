# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <algorithm>
# include <iostream>
# include <string.h>
using namespace std;

/*
 * 二叉树的定义:（链式存储）
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
 * 二叉树的递归遍历: 每次写递归，都按照这三要素来写
 * 1. 确定递归函数的参数和返回值： 确定哪些参数是递归的过程中需要处理的，
 * 那么就在递归函数里加上这个参数， 并且还要明确每次递归的返回值是什么进而确定递归函数的返回类型。
 * 2. 确定终止条件：写完了递归算法, 运行的时候，经常会遇到栈溢出的错误，就是没写终止条件或者终止条件写的不对，
 * 操作系统也是用一个栈的结构来保存每一层递归的信息，如果递归没有终止，操作系统的内存栈必然就会溢出。
 * 3. 确定单层递归的逻辑：确定每一层递归需要处理的信息。在这里也就会重复调用自己来实现递归的过程
 * 前序遍历: 中左右; 中序遍历: 左中右; 后序遍历: 左右中
 */
class Solution1_1 {
public:
    // 确定递归函数的参数和返回值, 因为要打印出前序遍历节点的数值，所以参数里需要传入vector在放节点的数值，
    // 除了这一点就不需要在处理什么数据了也不需要有返回值，所以递归函数返回类型就是void
    void traversal(TreeNode* cur, vector<int>& vec) {
        // 确定终止条件：在递归的过程中，如何算是递归结束了呢，当然是当前遍历的节点是空了，那么本层递归就要要结束了
        if (cur == NULL) return;
        // 确定单层递归的逻辑：前序遍历是中左右的循序，所以在单层递归的逻辑，是要先取中节点的数值，代码如下
        vec.push_back(cur->val);    // 中
        traversal(cur->left, vec);  // 左
        traversal(cur->right, vec); // 右
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return {};
        traversal(root, result);
        return result;
    }
};
class Solution1_2 {
public:
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        traversal(cur -> left, vec);
        vec.push_back(cur -> val);
        traversal(cur -> right, vec);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return {};
        traversal(root, res);
        return res;
    }
};
class Solution1_3 {
public:
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        traversal(cur -> left, vec);
        traversal(cur -> right, vec);
        vec.push_back(cur -> val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return {};
        traversal(root, res);
        return res;
    }
};

/*
 * 二叉树的迭代遍历: 手工栈模拟内存栈
 * 在迭代的过程中，其实我们有两个操作：
 * 1) 处理：将元素放进result数组中
 * 2) 访问：遍历节点
 * -----------------------------------------------------------------------------------------------
 * 分析一下为什么写的前序遍历的代码，不能和中序遍历通用呢，因为前序遍历的顺序是中左右，
 * 先访问的元素是中间节点，要处理的元素也是中间节点，所以刚刚才能写出相对简洁的代码，
 * 因为要访问的元素和要处理的元素顺序是一致的，都是中间节点。
 * 再看看中序遍历，中序遍历是左中右，先访问的是二叉树顶部的节点，然后一层一层向下访问，直到到达树左面的最底部，
 * 再开始处理节点（也就是在把节点的数值放进result数组中），这就造成了处理顺序和访问顺序是不一致的。
 * 即: 处理顺序从左node开始 访问顺序从中node开始
 * -----------------------------------------------------------------------------------------------
 * 前序遍历: 中左右; 中序遍历: 左中右; 后序遍历: 左右中
 * 会发现: 前序遍历处理顺序和访问顺序一致, 迭代好写; 后序遍历与前序遍历顺序差不多相反, 所以可以通过反转前序的结果得到 也好写
 * 不好写的就是中序遍历 需要指针额外记录 需要先访问到最底层的左节点 再开始遍历的记录
 */
class Solution2_1 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == NULL) return res;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top(); // root节点 也就是中节点
            res.push_back(node -> val); // 记录中间节点值 遍历的中左右的中
            st.pop();
            // 先右后左 出栈才是左右
            if (node -> right) st.push(node -> right); 
            if (node -> left) st.push(node -> left); 
        }
        return res;
    }
};
class Solution2_2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != NULL || !st.empty()) {
            if (cur != NULL) { // 指针来访问节点，访问到最底层
                st.push(cur); // 将访问的节点放进栈
                cur -> left; // 左
            }
            else {
                // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                cur = st.top(); // 栈最外层的是最底层的左node
                st.pop();
                res.push_back(cur -> val);
                cur = cur -> right;
            }
        }
        return res;
    }
};
class Solution2_3 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == NULL) return res;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top(); // root节点 也就是中节点
            res.push_back(node -> val); // 记录中间节点值 遍历的中左右的中
            st.pop();
            // 先左后右 出栈才是右左, 最后反转才是左右中
            if (node -> right) st.push(node -> right); 
            if (node -> left) st.push(node -> left); 
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/*
 * 二叉树的层序遍历: BFS广度优先搜索，一层一层的遍历
 * 需要借用一个数据结构，即队列来实现，队列先进先出符合一层一层遍历的逻辑，而是用栈先进后出适合模拟DFS也就是递归的逻辑。
 * 而这种层序遍历方式就是图论中的广度优先遍历，只不过我们应用在二叉树上
 */
class Solution3_1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que; // 声明队列 用来存每一层的所有node
        if (root != NULL) que.push(root); // 把root放进去(第0层)
        vector<vector<int>> res; // 存最后结果
        // 开始访问 并 遍历
        while (!que.empty()) {
            int size =que.size(); // 确定每一层的节点数量
            vector<int> vec; // 存每一层的结果
            // 每一层的访问 与 遍历
            for (int i = 0; i < size; i++) {
                // 从前往后记录所有节点的val值 这也是为什么用que而不是stack的原因
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node -> val);
                // 开始存下一层的node
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
            // 把每一层的结果放到一起
            res.push_back(vec); 
        }
        return res;
    }
};
/*
 * 二叉树的层次遍历 II 给定一个二叉树，返回其节点值自底向上的层次遍历
 */ 
class Solution3_2 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node -> val);
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
            res.push_back(vec);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/*
 * 二叉树的右视图, 给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
 */ 
class Solution3_3 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == size - 1) res.push_back(node -> val);
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
        }
        return res;
    }
};
/*
 * 二叉树的层平均值。给定一个非空二叉树, 返回一个由每层节点平均值组成的数组。
 */ 
class Solution3_4 {
public:
    vector<int> averageOfLevels(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            double avg = 0;
            double sum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                sum += node -> val;
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
            avg = sum / size;
            res.push_back(avg);
        }
        return res;
    }
};
/*
 * 513. 找树左下角的值 BFS
 */
class Solution6_3 {
private:
    int res = 0;
public:
    int levelOrder(TreeNode* root) {
        queue<TreeNode*> que; // 声明队列 用来存每一层的所有node
        if (root != NULL) que.push(root); // 把root放进去(第0层)
        // 开始访问 并 遍历
        while (!que.empty()) {
            int size =que.size(); // 确定每一层的节点数量
            // 每一层的访问 与 遍历
            for (int i = 0; i < size; i++) {
                // 从前往后记录所有节点的val值 这也是为什么用que而不是stack的原因
                TreeNode* node = que.front();
                que.pop();
                if (i == 0) this->res = node -> val;
                // 开始存下一层的node
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
        }
        return this->res;
    }
};
/*
 * N叉树的层序遍历
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
class Solution3_5 {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> que; 
        if (root != NULL) que.push(root); 
        vector<vector<int>> res; 
        while (!que.empty()) {
            int size =que.size(); 
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                Node* node = que.front();
                que.pop();
                vec.push_back(node -> val);
                for (int i = 0; i < node->children.size(); i++){
                    if (node -> children[i]) que.push(node -> children[i]);
                }
            }
            res.push_back(vec); 
        }
        return res;
    }
};
/*
 * 116/117. 填充每个节点的下一个右侧节点指针 (一个二叉树不止有左右节点 多出来next指针要指向下一个右侧节点)
 * 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL
 */ 
// Definition for a Node.
class NodeP {
public:
    int val;
    NodeP* left;
    NodeP* right;
    NodeP* next;

    NodeP() : val(0), left(NULL), right(NULL), next(NULL) {}

    NodeP(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    NodeP(int _val, NodeP* _left, NodeP* _right, NodeP* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
class Solution3_6 {
public:
    NodeP* connect(NodeP* root) {
        vector<int> res;
        queue<NodeP*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            NodeP* nodePre;
            NodeP* node;
            for (int i = 0; i < size; i++) {
                if (i == 0) {
                    nodePre = que.front();
                    que.pop();
                    node = nodePre;
                } else {
                    node = que.front();
                    que.pop();
                    nodePre -> next = node;
                }
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
            }
            nodePre -> next = NULL;
        }
        return root;
    }
};
/*
 * 二叉树的最大深度
 * 给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。说明: 叶子节点是指没有子节点的节点。
 */ 
// 迭代BFS
class Solution4_1 {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int depth = 0;
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            depth++;
        }
        return depth;
    }
};
// 递归DFS
class Solution {
public:
    int DFS(TreeNode* root) {
        if (root == nullptr) return 0;
        else {
            int left = DFS(root->left);
            int right = DFS(root->right);
            return max(left, right) + 1;
        }
    }
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        else return DFS(root);
    }
};
/*
 * 二叉树的最小深度
 * 给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。说明: 叶子节点是指没有子节点的节点。
 */ 
class Solution4_2 {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int depth = 0;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            depth++;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node -> val);
                if (node -> left) que.push(node -> left);
                if (node -> right) que.push(node -> right);
                if (!node -> left && !node -> right) return depth;
            }
        }
        return depth;
    }
};
/*
 * 543. 二叉树的直径
 */ 
class Solution {
   int maxlen = 0;
private:
    int dfs(TreeNode* root) { 
        if (root == nullptr) return 0;
        int leftSize = dfs(root->left);
        int rightSize = dfs(root->right);
        maxlen = max(maxlen, leftSize + rightSize); // 将每个节点最大直径当前最大值比较并取更大者
        return max(leftSize, rightSize) + 1; // 返回节点深度
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return maxlen;
    }
};
/*
 * 226.翻转二叉树(对称)
 */
class Solution5_1 {
public:
    bool compareTree(TreeNode* left, TreeNode* right) {
        // 先判断有没有
        if (left == nullptr && right == nullptr) return true;
        else if (left == nullptr && right != nullptr) return false;
        else if (left != nullptr && right == nullptr) return false;
        else if (left->val != right->val) return false;
        // 此层没有问题 再递归向下
        return compareTree(left->left, right->right) && compareTree(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return false;
        return compareTree(root -> left, root -> right);
    }
};
/*
 * 100. 相同的树
 */
class Solution5_2 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL ^ q == NULL) return false;
        else if (p == NULL && q == NULL) return true;
        else if (p -> val != q -> val) return false;
        bool compareLeft = isSameTree(p -> left, q -> left);       // 左子树：左、 右子树：左
        bool compareRight = isSameTree(p -> right, q -> right);    // 左子树：右、 右子树：右
        bool SameTree = compareLeft && compareRight;                  // 左子树：中、 右子树：中（逻辑处理）
        return SameTree;
    }
};
/*
 * 222.完全二叉树的节点个数
 */
class Solution5_3 {
private:
    int getNodesNum(TreeNode* cur) {
        if (cur == NULL) return 0;
        int leftNum = getNodesNum(cur->left);      // 左
        int rightNum = getNodesNum(cur->right);    // 右
        int treeNum = leftNum + rightNum + 1;      // 中
        return treeNum;
    }
public:
    int countNodes(TreeNode* root) {
        return getNodesNum(root);
    }
};
/*
 * 110.平衡二叉树
 */
class Solution5_4 {
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
 * 257. 二叉树的所有路径
 */
class Solution6_1 {
    private:
    vector<string> DFS(TreeNode* cur, vector<int>& path, vector<string>& res) {
        path.push_back(cur -> val); // 得到当前节点值
        // 到了DFS最底层的叶子节点 说明递归到头了
        if (cur -> left == NULL && cur -> right == NULL) {
            string sPath;
            // path.size() - 1 指的是不要最后一个节点 免得循环里多出一个"->"
            for (int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            // 记录最后一个节点,因为上面的if判断会在最后一个节点处停下 这时最后一个节点没有进到path里，所以补上
            sPath += to_string(path[path.size() - 1]); 
            res.push_back(sPath); // 收集一个路径
        }
        if (cur -> left) {
            DFS(cur -> left, path, res);
            path.pop_back(); // path清零 方便下一次记录 算是回溯
        }
        if (cur -> right) {
            DFS(cur -> right, path, res);
            path.pop_back(); // path清零 方便下一次记录 算是回溯
        }
        return res;    
    }
    public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        vector<int> path;
        if (root != NULL) return DFS(root, path, res);
        else return res;
    }
};
/*
 * 124. 二叉树的最大路径和
 */
class Solution {
public:
    int res = INT_MIN;
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return res;
    }

    int dfs(TreeNode* root){
        if(root == nullptr)  return 0;
        int left = max(0, dfs(root->left)), right = max(0, dfs(root->right));
        res = max(res, root->val + left + right);
        return root->val + max(left, right);
    }
};
/*
 * 112. 路径总和
 * 不要去累加然后判断是否等于目标和，那么代码比较麻烦，可以用递减，让计数器count初始为目标和，然后每次减去遍历路径节点上的数值。
 * 如果最后count == 0，同时到了叶子节点的话，说明找到了目标和。
 * 如果遍历到了叶子节点，count不为0，就是没找到。
 */
class Solution6_2 {
private:
    int count = 0;
    bool DFS(TreeNode* cur, int count) {
        if (!cur -> left && !cur -> right && count == 0) return true;
        if (!cur -> left && !cur -> right) return false;
        if (cur -> left) {
            if(DFS(cur -> left, count - cur -> val)) return true;
        }
        if (cur -> right) {
            if(DFS(cur -> right, count - cur -> val)) return true;
        }
        return false;
    }
public:
    bool haspathsum(TreeNode* root, int sum) {
        if (root == nullptr) return false;
        return DFS(root, root -> val);
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
 * 404. 左子树之和
 */
class Solution6_3 {
    private:
    int res = 0;
    int sumLeft(TreeNode* root) {
        if (root == nullptr) return 0;
        // 左叶子不好通过当前节点判断 只能通过父节点判断
        if (root -> left != nullptr && root -> left -> left == nullptr && root -> left -> right == nullptr) this -> res += root -> left -> val;
        sumLeft(root -> left);
        sumLeft(root -> right);
        return res;
    }
    public:
    int sumOfLeftLeaves(TreeNode* root) {
        return sumLeft(root);
    }
};
/*
 * 654. 最大二叉树
 */
class Solution6_4 {
private:
    TreeNode* DFS(vector<int>& nums, int left, int right) {
        int maxValue = INT_MIN;
        int left = 0;
        int maxIndex = 0;
        if (left >= right) return nullptr;
        // 找到最大值 划分左右子树
        for (int i = left; i < right; ++i) {
            if (nums[i] > maxValue) {
                maxValue = nums[i];
                maxIndex = i;
            }
        }
        // 新建二叉树结构
        TreeNode* node = new TreeNode(nums[maxIndex]);

        node -> left = DFS(nums, left, maxIndex); // 左边新的nums

        node -> right = DFS(nums, maxIndex + 1, right); // 左边新的nums
        return node;

    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return DFS(nums, 0, nums.size());
    }
};
/*
 * 700. 二叉搜索树的搜索
 * 二叉搜索树要注意利用其特性：不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。
 */
class Solution7_1_1 {
private:
    TreeNode* DFS(TreeNode* root, int val) {
        if (root == nullptr) return NULL;
        if (root -> val == val) return root;
        if (root -> val > val) return DFS(root -> left, val);
        if (root -> val < val) return DFS(root -> right, val);
        return nullptr;
    }
public:
    TreeNode* searchBTS(TreeNode* root, int val) {
        return DFS(root, val);
    }
};
// 迭代法：一提到二叉树遍历的迭代法，可能立刻想起使用栈来模拟深度遍历，使用队列来模拟广度遍历
// 对于二叉搜索树的特殊性，也就是节点的有序性，可以不使用辅助栈或者队列就可以写出迭代法
// 对于二叉搜索树，不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。
class Solution7_1_2 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != NULL) {
            if (root->val > val) root = root->left;
            else if (root->val < val) root = root->right;
            else return root;
        }
        return NULL;
    }
};
/*
 * 98. 验证二叉搜索树
 * 注释掉的是错误滴 逻辑错误 是个陷阱 对BTS理解不到位
 * 应该看中序遍历，因为中序遍历是左中右 如果中序遍历是递增的 就是BTS
 */
// class Solution7_2 {
// private:
//     bool DFS(TreeNode* root) {
//         if (root == nullptr) return false;
//         if (root -> left -> val < root -> val && root -> right -> val > root -> val) return true;
//         return DFS(root -> left) && DFS(root -> right);
//     }
// public:
//     bool isValidBST(TreeNode* root) {
//         return DFS(root);
//     }
// };
class Solution7_2_1 {
private:
    long long maxVal = LONG_MIN;
    bool DFS(TreeNode* root) {
        if (root == nullptr) return true;
        bool left = DFS(root -> left);
        if (root -> val > maxVal) maxVal = root -> val;
        else return false;
        bool right = DFS(root -> right);
        return left && right;
    }
public:
    bool isValidBST (TreeNode* root) {
        return DFS(root);
    }
};
class Solution7_2_2 {
public:
    TreeNode* pre = NULL; // 用来记录前一个节点
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        bool left = isValidBST(root->left);

        if (pre != NULL && pre->val >= root->val) return false;
        pre = root; // 记录前一个节点

        bool right = isValidBST(root->right);
        return left && right;
    }
};
/*
 * 二叉搜索树采用中序遍历，其实就是一个有序数组
 * 530. 二叉搜索树的最小绝对差
 */
class Solution7_3_1 { // 转为数组 再遍历判断
private:
    vector<int> arr;
    void DFS(TreeNode* root) {
        if (root == nullptr) return;
        DFS(root->left);
        arr.push_back(root->val);
        DFS(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        arr.clear();
        DFS(root);
        if (arr.size() < 2) return 0;
        int res = INT_MAX;
        for (int i = 1; i < arr.size(); i++) {
            res = min(res, arr[i] - arr[i - 1]);
        }
        return res;
    }
};
class Solution7_3_2 { // 不转为数组 直接在遍历的节点上计算
private:
    int res = INT_MAX;
    TreeNode* pre;
    int DFS(TreeNode* cur) {
        if (cur == nullptr) return;
        DFS(cur->left);
        if (pre != nullptr) res = min(res, cur->val - pre->val);
        pre = cur;
        DFS(cur->right);
        return res;
    }
public:
    int getMinimumDifference(TreeNode* root) {
        return DFS(root);
    }
};
/*
 * 501. 二叉搜索树中的众数
 * 如果不是二叉搜索树，用哈希的话就得一个一个
 */
class Solution7_4 {
private:
    void DFS(TreeNode* node, unordered_map<int, int>& map) {
        if (node == nullptr) return;
        map[node->val]++;
        DFS(node->left, map);
        DFS(node->right, map);
        return;
    }
    bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }

public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> hash;
        vector<int> res;
        if (root == nullptr) return res;
        DFS(root, hash);
        vector<pair<int, int>> vec(hash.begin(), hash.end());
        sort(vec.begin(), vec.end(), cmp);
        res.push_back(vec[0].first);
        for (int i = 0; i < vec.size(); ++i) {
            if (vec[i].second == vec[0].second) res.push_back(vec[i].first);
        }
        return res;
    }
};
/*
 * 236. 二叉树的最近公共祖先
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 * 如果找到一个节点，发现左子树出现结点p，右子树出现节点q，
 * 或者左子树出现结点q，右子树出现节点p，那么该节点就是节点p和q的最近公共祖先
 */
class Solution8_1 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr && right == nullptr) return nullptr;
        if (left != nullptr && right == nullptr) return left;
        if (right != nullptr && left == nullptr) return right;
        else return root;
    }
};
/*
 * 本题是二叉搜索树，是有序的。在有序树里，如果判断一个节点的左子树里有p，右子树里有q呢？
 * 只要从上到下遍历的时候，cur节点是数值在[p, q]区间中则说明该节点cur就是最近公共祖先了。
 * 在遍历二叉搜索树的时候就是寻找区间[p->val, q->val]（注意这里是左闭又闭）
 * 那么如果 cur->val 大于 p->val，同时 cur->val 大于q->val，那么就应该向左遍历（说明目标区间在左子树上）
 */
// 递归法
class Solution8_2_1 {
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
// 迭代法
class Solution8_2_2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* node = root;
        while(1) {
            if (p->val < node->val && q->val < node->val) node = node->left;
            if (p->val > node->val && q->val > node->val) node = node->right;
            else break;
        }
        return node;
        // while(node) {
        //     if (p->val < node->val && q->val < node->val) node = node->left;
        //     if (p->val > node->val && q->val > node->val) node = node->right;
        //     else return node;
        // }
        // return NULL;
    }
};
/*
 * 701. 二叉搜索树的插入操作
 */
// 迭代
class Solution8_3 {
    private:
    TreeNode* DFS(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode* node = new TreeNode(val);
            return node;
        }
        if (root->val > val) root->left = DFS(root->left, val); // 根据二叉搜索树特性 判断节点值确定移动方向，递归，将值赋给节点
        if (root->val < val) root->right = DFS(root->right, val);
        return root;
    }
    public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        return DFS(root, val);
    }
};
/*
 * 450.删除二叉搜索树中的节点
 * 删除后可能有多种情况，主要是孩子节点进行补位
 */
class Solution8_4 {
private:
    TreeNode* DFS(TreeNode* root, int key) {
        if (root == NULL) return root; // 第一种情况：没找到删除的节点，遍历到空节点直接返回了
        if (root->val == key) {
            // 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
            if (root->left == nullptr) return root->right; //  第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
            else if (root->right == nullptr) return root->left; // 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
            // 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            // 并返回删除节点右孩子为新的根节点。
            else { // 找右子树最左面的节点
                TreeNode* cur = root->right;
                while (cur->left != nullptr) {
                    cur = cur->left; // 现在cur是右子树最左边的节点
                } 
                cur->left = root->left;
                TreeNode* tmp = root; //手动保存节点并删除内存
                root = root->right;
                delete tmp;
            }
        }
        if (root->val > key) root->left = DFS(root->left, key);
        if (root->val < key) root->right = DFS(root->right, key);
        return root;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        return DFS(root, key);
    }
};
/*
 * 669. 修建二叉搜索树
 * 修建就是找到不在范围内的点 删除 然后把子树接上来
 */
class Solution8_5 {
private:
    TreeNode* DFS(TreeNode* root, int l, int r) {
        if (root == nullptr) return NULL;
        if (root->val > r) return DFS(root->left, l, r);
        if (root->val < l) return DFS(root->right, l, r);
        root->left = DFS(root->left, l, r);
        root->right = DFS(root->right, l, r);
        return root;
    }
public:
    TreeNode* trimBST(TreeNode* root, int l, int r) {
        return DFS(root, l ,r);
    }
};
/*
 * 108. 将有序数组转换为二叉搜索树
 * BTS按后序遍历是一个递增数组，所以数组最中间的是根节点，左边是左子树 右边是右子树，类似二分找中间
 */
class Solution8_6 {
private:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + ((right - left) / 2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1);
        return root;
    }
};
/*
 * 538. 把二叉搜索树转换为累加树
 * 如果从树的角度来看，每个点的值要遍历。但是二叉树的中序遍历是递增数组 所以可以看作是前缀和
 * 但是由于每个节点的新值是大于当前节点值的加和, 所以递增数组里就是后缀和了
 * 为避免麻烦，选择倒过来的中序遍历(右中左)，这样遍历出来就是递减数组，填充新值的时候就是该数组的前缀和了
 */
class Solution8_7 {
    private:
    int pre; // 记录前一个节点的数值
    TreeNode* DFS(TreeNode* node) {
        if (node == nullptr) return node;
        DFS(node->right);
        node->val += pre;
        pre = node->val;
        DFS(node->left);
    }
    public:
    TreeNode* convertBST(TreeNode* root) {
        pre = 0;
        return DFS(root);
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
class Solution {
public:
    int numTrees(int n) {
        if(n <= 2) return n;
        vector<int> dp(n+1, 0);
        // int dp[n+1] ;
        // memset(dp ,0, sizeof(dp));
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++){
            for(int j = 1; j <= i; j++){
                dp[i] += (dp[j-1] * dp[i-j]);
            }
        }
        return dp[n];
    }
};
