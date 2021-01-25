// GH_CPP_CON_7

#include <iostream>
#include <memory>

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
    int m_var = -1;

    void myMemberFunction()
    {
        cout << "m_var = " << m_var << endl;
    }
};

void functionPointers()
{
    int a, b;
    int (*plus)(int, int) = addfunc;
    int (*minus)(int, int) = subtractfunc;

    a = operationfunc(7, 5, plus);
    b = operationfunc(20, a, minus);
    cout << "a = " << a << " and b = " << b << endl;
}

void memberFunctionPointers()
{
    MyClass myObj;
    void (MyClass::*pointerToMemberFunc)();

    pointerToMemberFunc = &MyClass::myMemberFunction;

    (myObj.*pointerToMemberFunc)();
}

void weakPointer()
{
    std::shared_ptr<int> sharedPointerObj = std::make_shared<int>(10);
    std::weak_ptr<int> weakPointerObj = sharedPointerObj;

    if (!weakPointerObj.expired())
    {
        cout << "Not expired" << endl;
        std::shared_ptr<int> sharedPointerObjFromWeak = weakPointerObj.lock();
    }

}

int main()
{
    functionPointers();
    memberFunctionPointers();
    weakPointer();

    return 0;
}
