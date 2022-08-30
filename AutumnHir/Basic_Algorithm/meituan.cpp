# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
using namespace std;

// 打字
int main() {
  
  int n;
  vector<int> v1;
  cin >> n;
  
  for(int i = 0; i < n; i++) {
    string str;
    int count = 0;
    cin >> str;
    
    for (int j = 0; j < str.size(); j++) {
        int num = int(str[j]);
        
        if(num >= 65 && num <= 90) {//大写字母的话 我们需要判断上个字母是大小写 
          if (j == 0) { //第一个字母是 大写的 默认是小写的 所以需要 shift
            count++;
          } else if (int(str[j-1]) >=90 ) {//上个字母是小写的 那么的话就要++了

            count++;
          }
          count++;//该字母
        } else { //小写的字母的话 
           if(j != 0 && int(str[j-1]) <= 90){ //上个字母是大写的
             count++;
           }
          count++;//该字母
        }
    }
    v1.push_back(count);
  }
  
  for(int i = 0; i < n; i++) {
    cout << v1[i];  
  }
  
  
  
}

// 二分
double x;
int main() {
    cin >> x;
    // 确定边界值
    double l = -100000, r = 100000;
    // 注意循环条件处理精度问题
    while (r - l > 1e-8) {
        // 步骤 A: 找中间值
        double mid = (l + r) / 2;
        // 步骤 B: 判断
        if (mid * mid * mid < x) l = mid;
        else r = mid;
    }
    printf("%.6f", r);
    return 0;
}
