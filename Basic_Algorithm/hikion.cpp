# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <map>
# include <stack>
# include <queue>
# include <string>
# include <algorithm>
using namespace std;

/*
 * coding 1
 */
vector<int> slidingwindow(vector<int>& data, int k) {
    vector<int> ret;
    if (data.size() == 0) return ret;
    deque<int> q;
    for (int i = 0; i < data.size(); i++) {
        while (!q.empty() && data[q.back()] < data[i])
        {
            q.pop_back();
        }
        q.push_back(i);
        if (k == i - q.front()) q.pop_front();
        if (i >= k - 1) ret.push_back(data[q.front()]);
    }
    return ret;
} 
int main() {
    vector<int> data={2,3,4,2,6,2,5,1};
    int i = 0;
    int num = 3;
    // do {
    //     cin >> i;
    //     if (i == '[') continue;
    //     if (i == ']') break;
    //     data.push_back(i);
    // } while(getchar() != '\n');
    // cin >> num;
    vector<int> res;
    res = slidingwindow(data, num);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << ',';
    }
    // cout << endl;
    return 0;
}