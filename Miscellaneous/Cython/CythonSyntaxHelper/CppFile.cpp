
#include<iostream>
#include<string>
#include<tuple>
using namespace std;
#include <thread>
#include <iostream>
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;


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

    class MyInnerClass
    {
        public:
        MyInnerClass();   
    int myInnerInt=100;
    };
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

struct MyException : public exception {
   const char * what () const throw () {
      return "C++ Exception";
   }
};
 

void throwException()
{
    throw MyException();
}


void myFuncTakingConst(const int a)
{
    std::cout << "myFuncTakingConst "<<  a<< std::endl;
}






void threadModule(int myInput)
{
      std::unique_lock<std::mutex> lck(mtx);
         while (!ready) cv.wait(lck);

    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
}

void unlockConditionVariable()
{
    std::cout << "Unlocking..." << std::endl;
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    lck.unlock();
    cv.notify_all();
    std::cout << "unlocked..." << std::endl;
}

void makeWaitWithCondVariable()
{
    std::cout << "start waiting..." << std::endl;
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready)
        cv.wait(lck);
    std::cout << "Gone out of waiting..." << std::endl;
}
