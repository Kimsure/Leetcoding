# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
using namespace std;

/*
 * 77. 组合: 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
 * 回溯法解决的问题都可以抽象为树形结构（N叉树）
 */
class Solution0_1 {
private:
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return res;
    }
};