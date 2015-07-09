#include<sys/sem.h> // System V implementation
#include<cstdio>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define THREAD_COUNT 2
#define SEM_COUNT 1 // No of semaphores need to be created

void semaphore_wait(int semid)
{
  struct sembuf sem_op[1];
  sem_op[0].sem_num=0;
  sem_op[0].sem_flg=SEM_UNDO;
  sem_op[0].sem_op=-1;

  semop(semid,sem_op,1);
}

void semaphore_signal(int semid)
{
  struct sembuf sem_op;
  sem_op.sem_num=0;
  sem_op.sem_flg=SEM_UNDO;
  sem_op.sem_op=1;

  semop(semid,&sem_op,1);

}



void init_semaphore(int semid)
{
  struct sembuf sem_op;
  sem_op.sem_num=0;
  sem_op.sem_flg=SEM_UNDO;
  sem_op.sem_op=1; // No of Resource can access at a time a single semaphore

  semop(semid,&sem_op,1);

}

void *thrfunction(void *param)
{
  int semid=*((int *)param);
  printf("\nThread %u created! waiting to aquire critical region...",(int)pthread_self());
  sleep(1);

  semaphore_wait(semid);
  printf("\nThread %u in critical section ",(int)pthread_self());
  printf("\n Free Resources at semaphore 0 after calling wait : %d",semctl(semid,0,GETVAL));
  sleep(5);
  semaphore_signal(semid);
  
  printf("\nThread %u out critical section ",(int)pthread_self());

}

int main()
{
  int sem_key=ftok("key.txt",'A');

  if(0 > sem_key)
  {
    perror("Error in getting key! (or) \"key.txt\" File not found. Cause: ");
    return errno;
  }

  int semid=semget(sem_key,SEM_COUNT,0); // IPC_CREAT BIT SHOULD NOT BE SET
  if(0 > semid)
  {
    perror("Error in creating semaphore! Cause:");
    return errno;
  }

  printf("\n Free Resources at semaphore 0 : %d",semctl(semid,0,GETVAL));

  /*Creating two threads */

  pthread_t threads[THREAD_COUNT];
  
  for(int i=0;i<THREAD_COUNT;i++)
  {
    pthread_create(&threads[i],NULL,thrfunction,&semid);
  }

  for(int i=0;i<THREAD_COUNT;i++)
  {
    pthread_join(threads[i],NULL);
  }


  return 0;
}
