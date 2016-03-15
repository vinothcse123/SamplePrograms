#include <iostream>
using namespace std;


class A
{
   public:
       explicit A(int a)  {cout << "constructor called \n " << a;}
};

void foo(const A a1){}

int callme(int a)
{

}

int main()
{
   // A b=10.2222; Not allowed
   A b(10.6554);
   return 0;
}
