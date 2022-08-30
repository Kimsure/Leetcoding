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

/*
 * '&'是取地址运算符(获取某个值对应的地址), '*'是间接运算符or取消引用运算符(获取某个地址对应的值)
 * double d;
 * int& s =d;  // 这里的'&'是引用运算符 不要和指针混淆
 */
/*
 * 今天看到char * 这一类型数据的大小为4个字节时，有点懵，char数据类型明明只占一个字节，为什么其指针却占四个字节呢？
 * 大家首先应该明白一个最基础的问题：数据的地址和数据本身没有任何关系，比如说 int a=10，a这个变量值为10，但是其地址却是一个和计算机处理器位数密切相关的值，
 * 如果是32位系统，那么其地址就是由这32根总线组合的某一个32位二进制数字串，八位是一个字节，那么32位就是4个字节，相对应的，64位就是8个字节。
 * 因此，char *说到底只是一个地址的序号，无论是char *p,还是double *p，其字节数(指针变量大小)只和计算机的位数相关，和其数据类型默认所占大小无关。
 * 64位操作系统下指针变量大小为8，32位操作系统下指针变量大小为4
 */
int num = 8;
void ChangePoint(int *p2)//入参类型为指针，则p2和p1是两个指针，两个指针指向的地址相同。
{
    int i = 0;
    int *p3 = &i;
    *p2 = num;//改变指针p2指向内容的值即改变了p1指向内容的值，及a的值也变为8。
    p2 = p3;//指针变量p2的改变，但不会影响到p1的指向。
    cout << "test changepoint" << endl;
    cout << p2 << ' ' << p3 << ' ' << endl;

}

void addressandvalue() {
    int num = 5;
    int value = 0;
    int* address = &(num);
    value = *&(num); // value = *&(num) = *address
    cout << "test addressandvalue" << endl;
    cout << "num value: " << value << ", num address: " << address << endl; 
}

void referandpointer() {
    int a = 5;
    int& b = a;
    int* add1 = &a;
    int* add2 = &b;
    cout << "test refandpointer" << endl;
    if (add1 == add2) {
        // 可以看出 a, b 两个变量共用同一个内存空间 地址相同
        cout << "address is same" << endl;
    }
    cout << a << ' ' << b << ' ' << add1 << ' ' << add2 << endl;
    // 通过对指针指向的地址使用'*'，测试获取某个地址对应的值
    cout << "test is ok " << *add1 << ' ' << *add2 << endl;
    // 通过对变量值使用'&'，测试获取某个值对应的地址
    cout << "test is ok " << &a << ' ' << &b << endl;
}

void multipointer() {
    int num = 5;
    int* ptr1 = &num;
    int** ptr2 = &ptr1; // 两个"**"才可以是指向指针的指针
    // int* ptr2 = ptr1; // 这种就是两个一样的但名字，内存空间不同的指针
    cout << "test multipointer" << endl;
    cout << "num value " << num << " ptr1 value " << ptr1 << " ptr2 value " << ptr2 << endl;
    cout << "num value " << *ptr1 << " ptr1 value " << *ptr2 << " ptr2 value " << ptr2 << endl;
}

int main()
{
    int a = 5;
    int *p1 = &a;
    ChangePoint(p1);//p1仍指向a，但a的值已经变为8。
    cout << *p1 << endl;
    addressandvalue();
    referandpointer();
    multipointer();
    return a;
}

