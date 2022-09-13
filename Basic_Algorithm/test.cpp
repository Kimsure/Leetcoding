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

// int main() {
//     stack<char> stk1;
//     stack<char> stk2;
//     stk1.push('(');
//     int a = stk1.top();
//     cout << a << ' ' << stk1.top();
//     return 0;
// }

int main() {
    int col = 0, row = 0, q = 0;
    cin >> col >> row >> q;
    cin.ignore();
    char s[col][row];
    for(int i = 0; i < col; i++) {
    // cout<<"\n请输入第"<<i+1<<"个字符串："<<endl;
        gets(s[i]);
    }
    for(int i = 0; i < col; i++) {
    // cout<<"\n请输入第"<<i+1<<"个字符串："<<endl;
        cout << s[i] << endl;
    }
    int a = 0, b = 0, c = 0;
    int index = 0;
    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c;
        index = a % (row*col);
        // for (int j = 0; j < index; j++) {

        // }

    }
}




