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

int main() {
    stack<char> stk1;
    stack<char> stk2;
    stk1.push('(');
    int a = stk1.top();
    cout << a << ' ' << stk1.top();
    return 0;
}
