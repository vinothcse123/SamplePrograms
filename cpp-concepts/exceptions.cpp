//GH_CPP_CON_8

#include<iostream>
#include <exception>
#include <thread>
#include <iostream>
#include <future>
#include <mutex>
using namespace std;
#include <condition_variable> // std::condition_variable

std::mutex g_mutex;
std::condition_variable cv;
int g_int=10;
bool g_isCondWaited=false;

void threadModule(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;


    throw "throwing exception in worker thread";
  
    
}

void threadModuleCondWait(int myInput)
{
    
    std::unique_lock<std::mutex> lck(g_mutex);
        
    if(!g_isCondWaited)
    {
        g_isCondWaited=true;
        std::cout << "Going to cond wait" << std::this_thread::get_id() << std::endl;
        cv.wait(lck);        
        
    }
    else
    {
        std::cout << "Throwing exception" << std::this_thread::get_id() << std::endl;
        //Before throwing exception, notify conditional waits to avoid blocking
         throw "throwing exception in worker thread";
    }
}




class Divide_by_zero : public std::exception
{
   public:
      const char* what() const throw()
      {
         return "User defined Exception :: Divide by zero !";
      }
};

void userDefinedException()
{
   Divide_by_zero d;

   try
   {
      int i;
      throw d;
   }
   catch(exception e)
   {
      printf("\nException Caught :: %s",e.what());
   }
}


void exceptionInThreads()
{
    try
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
    catch(...)
    {
        std::cout << "Exception in main thread" << std::endl;
    }

}

void exceptionInCondWaitThreads()
{
    try
    {

    

    using namespace std;

    std::thread threadArray[3];
    for (int i = 0; i < 3; i++)
    {
        threadArray[i] = thread(&threadModuleCondWait, 100);
    }

    for (int i = 0; i < 3; i++)
    {
        threadArray[i].join();
    }

    std::cout << "All thread completed" << std::endl;

    }
    catch(...)
    {
        std::cout << "Exception in main thread" << std::endl;
    }

}


int main()
{
   
   //userDefinedException();
    //exceptionInThreads();
    exceptionInCondWaitThreads();


   return 0;
}
