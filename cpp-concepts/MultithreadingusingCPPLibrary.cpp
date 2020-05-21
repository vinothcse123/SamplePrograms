#include <thread>
#include <iostream>

void threadModule(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
}

int main()
{
    std::thread threadObj(&threadModule,100);
    threadObj.join();   

    std::cout<<"All thread completed"<<std::endl;
 
    return 0;
}
