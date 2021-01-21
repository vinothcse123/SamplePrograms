//GH_CPP_CON_5

#include<iostream>
#include<cstdio>
#include<ctime> // In c it is <time.h>
#include<chrono> 
#include<thread> 

void printTimeStruct(tm *time_struct)
{
  printf("\n CURRENT YEAR :: %d ",  (time_struct->tm_year+1900)     );
   printf("\n CURRENT MON  :: %d ",  (time_struct->tm_mon+1)     );
   printf("\n CURRENT DAY  :: %d ",  time_struct->tm_mday     );
   printf("\n CURRENT HOUR :: %d ",  time_struct->tm_hour     );
   printf("\n CURRENT MIN  :: %d ",  time_struct->tm_min     );
   printf("\n CURRENT SEC  :: %d ",  time_struct->tm_sec     );
}

void getCurrentTimeUsingEpoch()
{
   using namespace std;

   time_t last_connect_time,current_time;
   struct tm *time_struct;
   char formatted_time[25];

   time(&last_connect_time);
   // -1 will be returned if not able to fetch caledar time
   std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
   current_time=time(0); // This is similar to time(&current_time)
   printf("\n DIFFERENCE TIME IN SECONDS  :: %f ", difftime(current_time,last_connect_time) );

   printf("\n Epoch time or unix time     :: %ld ",         current_time );

   time_struct = localtime(&current_time);
   printTimeStruct(time_struct);


   printf("\n asctime       :: %s ",     asctime(time_struct)     );
   strftime(formatted_time,sizeof(formatted_time),"%d-%b-%y",time_struct);
   printf("\n formatted_time:: %s ", formatted_time );

}

void prepareTimeAndConvertToEpoch()
{
    struct tm *time_struct;
    time_t currentTime=time(0);
    time_struct = localtime(&currentTime);
    time_struct->tm_year = 2020 - 1900;
    time_struct->tm_mon = 1 - 1;
    time_struct->tm_mday = 5;

    printf("\n mk_time to get epoch time again  :: %ld ",    mktime(time_struct) );
    printTimeStruct(time_struct);
}

int main()
{
   getCurrentTimeUsingEpoch();
   prepareTimeAndConvertToEpoch(); 

   return 0;
}
