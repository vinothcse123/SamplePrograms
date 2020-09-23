#include <thread>
#include <iostream>
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;


void threadModule(int myInput)
{
      std::unique_lock<std::mutex> lck(mtx);
         while (!ready) cv.wait(lck);

    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Input: " << myInput << std::endl;
}

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int main()
{
    using namespace std;
    std::thread threadObj(&threadModule,100);


     std::thread threadArray[3];
     for(int i=0;i<3;i++)
     {
         threadArray[i] = thread(&threadModule,100);
     }

    std::cout << "Notifying one thread..." << '\n';
     cv.notify_one();

     std::cout << "Notifying all thread..." << '\n';

     go();

    std::cout<<"All thread completed"<<std::endl;

        threadObj.join();   
      for(int i=0;i<3;i++)
     {
         threadArray[i].join();
     }
 
    return 0;
}
