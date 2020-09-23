#include <thread>
#include <iostream>

void threadModule(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
}

int main()
{
    using namespace std;
    std::thread threadObj(&threadModule,100);
    threadObj.join();   


     std::thread threadArray[3];
     for(int i=0;i<3;i++)
     {
         threadArray[i] = thread(&threadModule,100);
     }

      for(int i=0;i<3;i++)
     {
         threadArray[i].join();
     }

    std::cout<<"All thread completed"<<std::endl;
 
    return 0;
}
