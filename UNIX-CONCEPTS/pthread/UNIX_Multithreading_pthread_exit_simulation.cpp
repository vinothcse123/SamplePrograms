/* UNIX Multithreading pthread exit simulation */

#include<iostream>
#include "exploreme.h"

pthread_t thread1;

void* myFunction(void *param)
{

   printf("\n Going to exit the myFunction thread... ");
   sleep(1);
   pthread_exit(&thread1);

   printf("\n I am not visible! Since thread was exited");

   return 0;
}

int main()
{
   pthread_create(&thread1,NULL,myFunction,NULL);

   printf("\n Main thread Still Alive....");
   pthread_join(thread1,NULL);
   return 0;
}
