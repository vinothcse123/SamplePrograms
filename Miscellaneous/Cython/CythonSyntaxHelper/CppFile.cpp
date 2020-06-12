
#include<iostream>
#include<string>
#include<tuple>
using namespace std;



static void myCFunction()
{
    //std::cout << "Hello, My C++ is called from python !!!" << std::endl;
    printf("My C function is called from python! Superb\n");
}


static void sameFunctionNameinBoth()
{
    //std::cout << "Hello, My C++ is called from python !!!" << std::endl;
    printf("My testPxd function is called from python! Nice\n");
}


static void FunctionWithArgs(std::string myName)
{
    std::cout << "String received from python is "<<  myName<< std::endl;   
}


static void FunctionWithVector(std::vector<int> myVec)
{
    std::cout << "Vector is received Second element is "<<  myVec[1]<< std::endl;   
}

static void initUniquePtr(std::unique_ptr<int> &myUPtr)
{
    std::cout << "unique_ptr is set  "<<  1<< std::endl;   
    *myUPtr =6666;
}
static void FunctionWithUniquePtr(std::unique_ptr<int> &myUPtr)
{
    std::cout << "unique_ptr is received "<<  1<< std::endl;   
}

enum class MyEnum
{
    MyEnumValue1=200,
    MyEnumValue2
};

class MyCppClass
{
    public:
    int myInt=100;
    string myString;
    MyEnum myEnumObj;
};


void myFunctionTakingEnumClass(MyEnum myEnumObj)
{
    std::cout << "Enum received "<<  (int)myEnumObj<< std::endl;
}

template<typename T>
void myTemplateFunction(T a)
{
    std::cout << "myTemplateFunction "<<  a<< std::endl;
}

void functionTakingTuple(tuple<int,int> a)
{
    std::cout << "functionTakingTuple "<< 1<< std::endl;
}

bool myFunctionTakingClass(MyCppClass obj)
{
    std::cout << "myFunctionTakingClass - int"<< obj.myInt<< std::endl;
        std::cout << "myFunctionTakingClass -string "<< obj.myString<< std::endl;
        std::cout << "myFunctionTakingClass -Enum "<< (int)obj.myEnumObj<< std::endl;


}

bool returnBooleanValue()
{
    return true;
}

template<typename T>
class MyTemplateClass
{
    T a;
};
