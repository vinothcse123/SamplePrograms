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
	printf("\nThread %d entered", a);
	fflush(stdout);
	pthread_mutex_lock(&mutex_c1);

	
	printf("\n Thread %d in critical area",a);
	printf("\n Mutex will be unlocked, since i am calling wait....");
	pthread_cond_wait(&l_cond_var,&mutex_c1);
	sleep(3);
	printf("\n Got signal from main thread... Thank you main thread...Now mutex will be locked Magically....");
	printf("\n Thread %d out critical area",a);
}



int main()
{
	pthread_t thread1;

	pthread_cond_init(&l_cond_var,NULL);
	int a=0;
	pthread_create(&thread1,NULL,myFunction,&++a);
	
	sleep(1);
	printf("\n Thread 1 waiting for signal... I(pthread_cond_signal) am going to give in another 5 sec....");
	sleep(5);
	pthread_cond_signal(&l_cond_var);


	pthread_join(thread1,NULL);


	
	return 0;
}
