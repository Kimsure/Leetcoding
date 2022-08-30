# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
using namespace std;



int main() {
    int num = 0;
    int time = 0;
    cin >> num >> time;
    int array[num];
    int subs[num];
    for (int i = 0; i < num; i++) {
        cin >> array[i];
    }
    for (int i = 0; i < num; i++) {
        subs[i] = 0;
    }
    for (int j = 0; j < time; j++) {
        for (int i = 0; i < num; i++) {
            if (i == 0) {
                if (array[i] % 2 != 0) {
                    subs[i + 1] += (array[i] - 1) / 2;
                    subs[num - 1] += (array[i] - 1) / 2;
                    array[i] = 1;
                }
                else {
                    subs[i + 1] += array[i] / 2;
                    subs[num - 1] += array[i] / 2;
                    array[i] = 0;
                }
            }
            else if (i == num - 1) {
                if (array[i] % 2 != 0) {
                    subs[i - 1] += (array[i] - 1) / 2;
                    subs[0] += (array[i] - 1) / 2;
                    array[i] = 1;
                }
                else {
                    subs[i - 1] += array[i] / 2;
                    subs[0] += array[i] / 2;
                    array[i] = 0;
                }
            }
            else {
                if (array[i] % 2 != 0) {
                    subs[i - 1] += (array[i] - 1) / 2;
                    subs[i + 1] += (array[i] - 1) / 2;
                    array[i] = 1;
                }
                else {
                    subs[i - 1] += array[i] / 2;
                    subs[i + 1] += array[i] / 2;
                    array[i] = 0;
                }
            }
        }
        for (int i = 0; i < num; i++) {
          array[i] += subs[i];
          subs[i] = 0;
        }
    }
    for (int i = 0; i < num; i++) {
        cout << array[i] << ' ';
    }
    return 0;
}


// int main() {
//     unordered_map<char, int> st;
//     vector<string> vec;
//     ios::sync_with_stdio(false);
//     cin.tie(0);

    

// }