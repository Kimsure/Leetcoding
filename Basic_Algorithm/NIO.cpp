# include <iostream>
# include <vector>
using namespace std;


class Solution1 {
public:
    vector<int> sortCar (vector<int>& nums) {
        int a = 0, b = 0, c = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) a++;
            if (nums[i] == 1) b++;
            if (nums[i] == 2) c++;
        }
        for (int i = 0; i < a; i++) {
            nums[i] = 0;
        }
        for (int i = a; i < a + b; i++) {
            nums[i] = 1;
        }
        for (int i = a + b; i < a + b + c; i++) {
            nums[i] = 2;
        }
        
        return nums;
    }
};

int main() {
    Solution1 s1;
    vector<int> a = {0,1,2,2,0,1};
    vector<int> b = s1.sortCar(a);
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << ' ';
    }
    cout << endl;
}

// struct A {
//     char a1;
//     void* a2;
//     int a3;
// };
// struct B
// {
//     int b1;
//     struct A b2;
//     char b3;
// };

// int main() {
//     cout << sizeof(struct B) << endl;
//     return 0;
// }

// int main() {
//     double c = 0.0;
//     char d = '0';
//     double* a = & c;
//     char* b = & d;
//     cout << a << ' ' << b << endl;
//     a++;
//     b++;
//     cout << a << ' ' << b << endl;
//     return 0;
// }


