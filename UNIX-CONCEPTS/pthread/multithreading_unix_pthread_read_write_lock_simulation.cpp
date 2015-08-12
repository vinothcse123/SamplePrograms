/* multithreading unix pthread read write lock simulation */


#include<iostream>
#include<pthread.h>
#include<cstdio>
#include <unistd.h>

pthread_rwlock_t g_lock;

void* myFunction(void* param)
{
   int a=*(int *)param;
   printf("\nThread %d waiting to acquire lock...", a);
   fflush(stdout);

   /* Getting the write lock */

   pthread_rwlock_wrlock(&g_lock);
   printf("\n Thread %d in critical area for writing...",a);
   sleep(2);
   pthread_rwlock_unlock(&g_lock);

   printf("\n Thread %d out critical area",a);

}


int main()
{
   pthread_t thread1;
   pthread_rwlock_init(&g_lock,NULL);
   int a=0;
   pthread_create(&thread1,NULL,myFunction,&++a);
   pthread_join(thread1,NULL);

   pthread_rwlock_destroy(&g_lock);



   return 0;
}
