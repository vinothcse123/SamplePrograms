#include <iostream>

using namespace std;

int addfunc(int first, int second)
{
   return first + second;
}

int subtractfunc(int first, int second)
{
   return first - second;
}

int operationfunc(int first, int second, int (*functocall)(int, int))
{
   return (*functocall)(first, second);
}

class MyClass
{
    public:
    int m_var=-1;

    void myMemberFunction()
    {
        cout << "m_var = " << m_var << endl;

    }

    
};

int main()
{
   int  a, b;
   int  (*plus)(int, int) = addfunc;
   int (*minus)(int, int) = subtractfunc;

   a = operationfunc(7, 5, plus);
   b = operationfunc(20, a, minus);
   cout << "a = " << a << " and b = " << b << endl;

   
    MyClass myObj;
    void (MyClass::*pointerToMemberFunc)();
    
   pointerToMemberFunc = &MyClass::myMemberFunction;

   (myObj.*pointerToMemberFunc)();

   return 0;
}
