#include<iostream>
#include<string>
#include<vector>
#include <future>
#include <chrono>

using std::vector;
using std::cout;
using std::string;

struct MyClass
{
        std::future<bool> futureObj;

~MyClass()
{
        std::cout << " ==============V6P: Destructor ==================" << std::endl;

}
};

bool threadFuncExceptionInMainThread(int a)
{

    std::cout << " ==============V6P: threadFuncExceptionInMainThread ==================" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    std::cout << " ==============V6P: End of threadFuncExceptionInMainThread ==================" << std::endl;

    return true;
}

void exceptionInMainThread()
{
    MyClass obj;
    try
    {
        obj.futureObj=std::async(threadFuncExceptionInMainThread,100);
        throw std::runtime_error("Exception occured in main thread");
    }
    catch(...)
    {
        //Ensure all child threads is finished
        obj.futureObj.get();
        std::rethrow_exception(std::current_exception());
    }
    
}

int main()
{
    try
    {
    exceptionInMainThread();

    }
    catch(...)
    {

    }

    return 0;
}
