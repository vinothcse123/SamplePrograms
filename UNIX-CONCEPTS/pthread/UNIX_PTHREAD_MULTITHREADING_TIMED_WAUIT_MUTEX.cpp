#include<iostream>

pthread_mutex_t g_mutex;

void* threadproc(void *p)
{
   printf("\n Going to lock...");
   pthread_mutex_lock(&g_mutex);
   int ret=pthread_mutex_timedlock(&g_mutex,&l_timeSpec);
   printf("\n  :: %d ", ret );
   pthread_mutex_timedlock(&g_mutex,&l_timeSpec);
   printf("\n  :: %u ", g_mutex );
   return NULL;
}

void* threadproc2(void *p)
{
   struct timespec l_timeSpec;
   memset(&l_timeSpec,0,sizeof(l_timeSpec));
   l_timeSpec.tv_sec=50;
   printf("\n  :: %u ", g_mutex );
   pthread_mutex_lock(&g_mutex);
   int ret=pthread_mutex_timedlock(&g_mutex,&l_timeSpec);
   printf("\n  :: %d ", ret );
   pthread_mutex_timedlock(&g_mutex,&l_timeSpec);
   printf("\n  :: %u ", g_mutex );
   return NULL;

   return NULL;
}

int main()
{
   pthread_t l_thread,l_thread2;
   pthread_mutex_init(&g_mutex,NULL);
   pthread_create(&l_thread,NULL,threadproc,NULL);
   pthread_create(&l_thread2,NULL,threadproc,NULL);
   pthread_join(l_thread,NULL);
   pthread_join(l_thread2,NULL);

   return 0;
}
