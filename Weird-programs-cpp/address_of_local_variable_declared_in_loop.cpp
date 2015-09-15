/* address of local variable declared in loop */

#include<iostream>

int main()
{
   int i=0;

   while(i++  < 2)
   {
      int local_variable=0;
      printf("\n  :: %u ", &local_variable );
   }


   return 0;
}
