# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
# include<algorithm>
using namespace std;

/*
 * oppo后端研发，三数之和，概率题模拟，三个数的公倍数
 * oppo后端开发，数组返回能组成的最大数字，无序链表合并，dp爬楼梯问题
 */
// 三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) return res;
            if (i >= 1 && nums[i] == nums[i - 1]) continue;
            int l = i + 1, r = nums.size() - 1;
            while (r > l) {
                if (nums[l] + nums[r] + nums[i] < 0) l++;
                else if (nums[l] + nums[r] + nums[i] > 0) r--;
                else {
                    res.push_back(vector<int> {nums[i], nums[l], nums[r]});
                    while (r > l && nums[l] == nums[l + 1]) l++;
                    while (r > l && nums[r] == nums[r - 1]) r--;
                    l++;
                    r--;
                }
            } 
        }
        return res;
    }
};
// 三个数的最小公倍数，肯定能被最大的数整除
class Solution {
public:
    int myMax(int a, int b, int c) {
        if (a > b && a > c) return a;
        if (b > a && b > c) return b;
        if (c > a && c > b) return c;
    }
    int CommonMulti (int &a, int &b, int &c) {
        int res = 0;
        int k = myMax(a, b, c);
        int i = 1;
        while (1) {
            res = k*i;
            if (res % a == 0 && res % b == 0 && res % c == 0) break;
            else i++;
        }
        return res;
    }
};
//数组返回能组成的最大数字

class Solution {
private:
    static bool cmp(const int& a, const int& b) {
        string sa = to_string(a);
        string sb = to_string(b);
        return sa + sb > sb + sa;
    }
public:
    string largestNumber(vector<int>& nums) {
        string ans;
        sort(nums.begin(), nums.end(), cmp);
        for (int& t : nums) {
            ans += to_string(t);
        }
        if (ans[0] == '0') {  // 不能是00000
            return "0";
        }
        return ans;
    }
};





/*
 * 华为8.31
 */
// 单词替换
void change(string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
    }
}
bool check(char aa){
    if(aa>='A' && aa<='Z') return true;
    if(aa>='a' && aa<='z') return true;
    return false;
}
int main() {
    map<string, int> hash;
    string s;
    string s1;
    getline(cin, s);
    // cout << s;
    int t = 1;
    while(cin >> s1) {
        // cout << s1;
        change(s1);
        hash[s1] = t;
        t++;
    }
    string ans;
    int begin1 = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '"') {
            i++;
            while (i < s.size() && s[i] != '"') i++;
        }
        while(i < s.size() && check(s[i])) i++;
        if(i == s.size()) break;
        string tl = s.substr(begin1, i-begin1);
        begin1 = i + 1;
        string ts = tl;
        change(tl);
        if (hash[tl] != 0) ans += to_string(hash[tl] - 1);
        else ans += ts;
    }
    cout << ans << endl;
    return 0;
}
// 士兵任务
struct node
{
    int x, y, t;
    node() {}
    node(int a, int b, int c) : x(a), y(b), t(c) {}
    bool operator<(const node &a) const
    {
        return t > a.t;
    }
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int g[30][30], vis[30][30];
int n, m, ans = 0;
priority_queue<node> q;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> g[i][j];
            if (g[i][j] == 2)
            {
                vis[i][j] = 1; // 已经走过的地方
                q.push(node(i, j, 0));
            }
        }
    }
    while (!q.empty())
    {
        node cur = q.top();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int tx = cur.x + dx[i];
            int ty = cur.y + dy[i];
            if (tx < 0 || ty < 0 || tx >= n || ty >= n || vis[tx][ty] || g[tx][ty] == 1)
                continue;
            if (g[tx][ty] == 3)
            {
                ans = cur.t + 1;
                break;
            }
            vis[tx][ty] = 1;
            if (g[tx][ty] == 4)
                q.push(node(tx, ty, cur.t + 3));
            else if (g[tx][ty] == 6)
            {
                q.push(node(tx, ty, cur.t + 1));
                for (int j = 0; j < 4; ++j)
                {
                    int xx = tx + dx[j];
                    int yy = ty + dy[j];
                    if (g[xx][yy] == 1)
                        g[xx][yy] = 0;
                }
            }
            else
                q.push(node(tx, ty, cur.t + 1));
        }
        if (ans)
            break;
    }
    cout << ans;
    return 0;
}
// 公路休息站充电规划
/*
 * 京东8.27
 */