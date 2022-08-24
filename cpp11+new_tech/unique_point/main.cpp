# include <iostream>
# include <memory>
// 因为vscode一次编译所有cpp搞makefile太麻烦了 所以不写头文件 写在一个cpp里
// # include "cat.h"
// # include "cat.cpp"
using namespace std;
class Cat {
    public:
    Cat(std::string name);
    Cat() = default;
    ~Cat();

    void cat_info() const {
        std::cout << "cat info name : " << name << std::endl;
    }
    std::string get_name() const {
        return name;
    }
    void set_cat_name(const std::string &name) {
        this->name = name;
    }    
    private:
    std::string name{"Mimi"};
};

Cat::Cat(std::string name) : name(name) {
    std::cout << "Constructor of Cat : " << name << std::endl;
    
}
Cat::~Cat()
{
    std::cout << "Destructor of Cat " << name << std::endl;
}

int main() {
    Cat c1("OK");
    c1.cat_info();
    // int a = 0;
    {
        // int b = 0; // 这里a是在内部中括号的局部作用域，括号外调用不到
        Cat c1("OK");
        c1.cat_info();    
    }
    // cout << a << ' ' << b << endl;

    // row pointer
    Cat *c_p1 = new Cat("RowPointer");   // 发现这全局作用域里没有调用析构
    c_p1->cat_info();   
    {
        Cat *c_p1 = new Cat("RowPointer");
        c_p1->cat_info();   // 发现这局部作用域里没有调用析构
        delete c_p1;
    }
    delete c_p1; // 因为new出来的本来就得delete, delete调用析构
    // row pointer int* []
    int* i_p1 = new int(100);
    {
        // int* i_p1 = new int(200); // 声明只在作用域里，外部输入 != 200
        i_p1 = new int(200); // 这时候是重新给地址，外部返回为200
        delete i_p1; // 这时候已经析构了i_p1指针，外部就已经没有了这个指针 如果外部再delete会崩，
    }
    // delete i_p1;  // 外部就已经没有了这个指针 不需要再delete，说明row pointer不安全 易混
    // cout << *i_p1 << endl;


    // unique pointer
    Cat *c_p2 = new Cat("Unique Pointer");
    // 第一种：指向row pointer来得到unique pointer,
    std::unique_ptr<Cat> u_c_p2{c_p2}; 
    u_c_p2->cat_info(); 
    // // 但是会有以下
    // // row pointer c_p2仍然可以用
    // // c_p2->cat_info();
    // // u_c_p2->cat_info();
    // // c_p2->set_cat_name("Unique Pointer change");
    // // row pointer更改后, unique pointer也会更改
    // // u_c_p2->cat_info();
    // delete c_p2;
    // c_p2 = nullptr;
    // 在删除一个指针之后，一定将该指针设置成空指针（即在delete *p之后一定要加上： p=NULL）
    // 一个非常重要的概念：我们在删除一个指针之后，编译器只会释放该指针所指向的内存空间，而不会删除这个指针本身。
    cout << "row pointer c_p2 address : " << c_p2 << endl;
    cout << "unique pointer u_c_p2 address : " << u_c_p2.get() << endl;
    // u_c_p2->cat_info(); // ？

    // 第二种：new
    std::unique_ptr<Cat> u_c_p3{new Cat("Unique Pointer2")};
    u_c_p3->cat_info();
    u_c_p3->set_cat_name("Unique Pointer2-change");
    u_c_p3->cat_info();

    // 第三种：std::make_unique(推荐)
    std::unique_ptr<Cat> u_c_p4 = make_unique<Cat>("Unique Pointer3");
    u_c_p4->cat_info();
    u_c_p4->set_cat_name("Unique Pointer3-change");
    u_c_p4->cat_info();

    // 打印unique pointer地址
    cout << "unique pointer u_c_p4 address : " << u_c_p4.get() << endl;
    // 解引用
    std::unique_ptr<int> u_i_p4 = make_unique<int>(200);
    cout << *u_i_p4 << endl;

    cout << "process over" << endl;
    return 0;
}