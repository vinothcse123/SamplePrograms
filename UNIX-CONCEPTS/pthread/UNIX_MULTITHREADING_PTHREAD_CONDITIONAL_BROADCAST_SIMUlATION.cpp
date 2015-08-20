/* UNIX_MULTITHREADING_PTHREAD_CONDITIONAL_BROADCAST_SIMUlATION.cpp */


#include<iostream>
#include<pthread.h>
#include<cstdio>
#include <unistd.h>
#include<cstdio>
#include<unistd.h>

pthread_mutex_t mutex_c1;
pthread_cond_t l_cond_var=PTHREAD_COND_INITIALIZER;



void* myFunction(void* param)
{
  int a=*(int *)param;
  fflush(stdout);
  pthread_mutex_lock(&mutex_c1);


  printf("\n Thread %d waiting for broadcast... ",a);
  pthread_cond_wait(&l_cond_var,&mutex_c1);
  printf("\n Got broadcast signal from main thread for thread %d...",a);

  printf("\n Thread %d in critical area...",a);
  fflush(stdout);
  sleep(5);
  pthread_mutex_unlock(&mutex_c1);
  printf("\n Thread %d out critical area...",a); 
}



int main()
{
  pthread_t thread1;

  pthread_cond_init(&l_cond_var,NULL);
  int a=0;
  pthread_create(&thread1,NULL,myFunction,&++a);
  sleep(1);
  pthread_create(&thread1,NULL,myFunction,&++a);
  
  
  sleep(5);
  pthread_cond_broadcast(&l_cond_var);


  pthread_join(thread1,NULL);



  return 0;
}
