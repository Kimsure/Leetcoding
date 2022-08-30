# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
# include <algorithm>
using namespace std;

/*
 * coding 1 魔法外卖
 */
// int main() {
//     int num = 0, time = 0;
//     int magiCount = 0;
//     int tmp = 0;
//     cin >> num >> time;
//     int totalTime[num];
//     for (int i = 0; i < num; i++) {
//         cin >> totalTime[i];
//     }
//     // cout << num << ' ' << time << ' ' << endl;
//     tmp = totalTime[0];
//     // cout << tmp << endl;
//     if (tmp < time) magiCount++;
//     if (tmp >= time*num) {
//         cout << magiCount;
//         return 0;
//     }
//     for (int i = 1; i < num; i++) {
//         // cout << totalTime[i] << ' ';
//         if (totalTime[i] - tmp < time) magiCount++;
//         else if (totalTime[i] - tmp == time) tmp += time;
//         // cout << magiCount << ' ';
//     }
//     cout << magiCount;
//     return 0;
// }

/*
 * coding 2 扑克洗牌，顶部拿到底部
 */
int main() {
    deque<int> deq;
    int num = 0;
    cin >> num;
    vector<int> vec(num, 0);
    for (int i = 0; i < num; i++) {
        cin >> vec[i];
    }
    reverse(vec.begin(), vec.end());
    for (int i = 0; i < num; i++) {
        // cout << vec[i] << ' ';
        deq.push_front(vec[i]);
        for (int j = 0; j < 2; j++) {
            int tmp1 = deq.back();
            deq.pop_back();
            deq.push_front(tmp1);
        }
    }
    for (deque<int>::iterator i = deq.begin(); i != deq.end(); ++i) {
        cout << *i << ' ';
    }
    return 0;
}