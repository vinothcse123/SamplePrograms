#include<iostream>

int main()
{
   using namespace std;

   char from[21]="12345687";

   printf("\n  :: %s ", from  );

   strcpy(from,from+2);

   printf("\n  :: %s ", from  );



   return 0;
}
