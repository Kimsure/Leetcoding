# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <string>
# include <algorithm>
using namespace std;

/*
 * coding 1
 */
// int main() {
//     int num = 0;
//     cin >> num;
//     char a[num];
//     char b[num];
//     for (int i = 0; i < num; i++) {
//         cin >> a[i];
//     }
//     for (int j = 0; j < num; j++) {
//         cin >> b[j];
//     }
//     vector<char> res;
//     int idx = 0;
//     while (idx < num) {
//         res.push_back(a[idx]);
//         res.push_back(b[idx]);
//         idx++;
//     }
//     for (int r = 0; r < res.size(); r++) {
//         cout << res[r];
//     }
//     return 0;
// }

/*
 * coding 2
 */
bool cmp (vector<int> &a, vector<int> &b) {
    return a[1] >= b[1];
}
int main() {
    int num = 0;
    int re = 0;
    cin >> num >> re;
    // float res = 0.00;
    vector<int> p(num);
    vector<int> fen(num);
    for (int i=0; i <num; i++) {
        cin >> p[i];
    }
    for (int i=0; i <num; i++) {
        cin >> fen[i];
    }
    vector<vector<int>> res0(num, vector<int>(2));
    for (int i=0; i <num; i++) {
        res0[i][0] = p[i];
        res0[i][1] = fen[i];
        // cout << res0[i][0] << ' ' << res0[i][1] << ' ' << res0[i][2] << endl;
    }

    sort(res0.begin(), res0.end(), cmp);
    double res;
    for (int i = 0; i < re; i++) {
        res += res0[i][1];
    }
    for (int i = re; i < num; i++) {
        res += res0[i][0] * res0[i][1] / 100;
    }
    printf("%.2f\n", res);
    return 0;
}