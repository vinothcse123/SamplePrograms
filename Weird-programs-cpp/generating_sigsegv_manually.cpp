#include<iostream>
#include <signal.h>

sigset_t g_signal_set;
struct sigaction sigact;


void catchcore(int sig)
{
   printf("\n signal :: %d ", sig );
   //abort();
}

int main()
{

   sigact.sa_handler = catchcore;

   sigaction(SIGSEGV,&sigact,NULL); // Comment this line if core file need to be generated.

   raise(SIGSEGV);

   return 0;
}
