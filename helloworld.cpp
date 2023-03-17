// VS Code C/C++ 测试代码 "Hello World"
// 由 VSCodeConfigHelper v3.1.6 生成

// 您可以在当前的文件夹（工作文件夹）下编写代码。

// 按下 Ctrl + F5 编译运行。
// 按下 F5 编译调试。
// 按下 Ctrl + Shift + B 编译，但不运行。

#include <iostream>
using namespace std;

/**
 * 程序执行的入口点。
 */
int main() {
    // 在标准输出中打印 "Hello, world!"
    int one[2][2] = {{1,2},{3,4}};
    // one[1][1] = {2};
    cout << *(&one+1) <<endl;
    cout << one <<endl;

    int a[5] = {5,6,7,8,9};
    int* b = (int*)(&a + 1);
    cout << &a << endl;
    cout << (int*)(&a + 1) << endl;
    cout << (int*)(&a + 2) << endl;
    cout << *b << endl;
    // cout 
    cout << *(a + 1) << *(b - 1);
    return 0;
}

// 此文件编译运行将输出 "Hello, world!"。
// 按下 F5 后，您将在下方弹出的终端（Terminal）窗口中看到这一行字。
// 重要提示：您以后编写其它代码时，请务必确保文件名不包含中文或特殊字符，切记！
// 如果遇到了问题，请您浏览
// https://github.com/Guyutongxue/VSCodeConfigHelper/blob/v2.x/TroubleShooting.md
// 获取帮助。如果问题未能得到解决，请联系开发者 guyutongxue@163.com。
