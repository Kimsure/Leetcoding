#include <iostream>
#include <stddef.h>
using namespace std;
#pragma pack(4) // 指定4字节对齐方式

struct  S
{
	int x;
	char y;
	int z;
	double a;
};
int main()
{
    S s;
	cout << offsetof(S, x) << endl; // 0
	cout << offsetof(S, y) << endl; // 4
	cout << offsetof(S, z) << endl; // 8
	cout << offsetof(S, a) << endl; // 12
    cout << sizeof(s) << endl;
	return 0;
}