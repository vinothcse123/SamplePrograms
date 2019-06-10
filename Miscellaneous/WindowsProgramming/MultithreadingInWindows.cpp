#include<iostream>
#include<process.h>
#include <windows.h>



void myThreadFunction(void *myData)
{
	std::cout<< "HAI";
}


int main()
{	
	using namespace std;

	HANDLE  myThreadHandle;
	DWORD   myThreadId;

	myThreadHandle = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            myThreadFunction,       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            &myThreadId);   // returns the thread identifier 
	
	
	WaitForSingleObject(myThreadHandle);
	
	return 0;
}
