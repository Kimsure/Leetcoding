# include <iostream>
 
using namespace std;
 
class Line {
   public:
      void setLength( double len );
      double getLength( void );
      // 类内成员函数定义
      int setWeight(int w) {
        this->length = w;
      }
      Line();  // 这是构造函数
 
   private:
      double length;
};
 
// 类外成员函数定义，包括构造函数
Line::Line(void) {
    cout << "Object is being created" << endl;
}
 
void Line::setLength( double len ) {
    length = len;
}
 
double Line::getLength( void ) {
    return length;
}
// 程序的主函数
int main( ) {
   Line l;
 
   // 设置长度
   l.setLength(6.0); 
   cout << "Length of line : " << l.getLength() <<endl;
 
   return 0;
}