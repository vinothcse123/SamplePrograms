//GH_CPP_CON_6

#include <thread>
#include <iostream>
#include <future>

void threadModule(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
}

int threadModuleWithReturn(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
    return myInput;
}

void mulithreadUsingStandardThread()
{
    using namespace std;
    std::thread threadObj(&threadModule, 100);
    threadObj.join();

    std::thread threadArray[3];
    for (int i = 0; i < 3; i++)
    {
        threadArray[i] = thread(&threadModule, 100);
    }

    for (int i = 0; i < 3; i++)
    {
        threadArray[i].join();
    }

    std::cout << "All thread completed" << std::endl;
}

void asyncAndFuture()
{
    std::future<int> fut = std::async (threadModuleWithReturn,1020);
    int ret = fut.get();      
    std::cout << "Async completed : " << ret<< std::endl;
}

int main()
{
    mulithreadUsingStandardThread();
    asyncAndFuture();
    return 0;
}
