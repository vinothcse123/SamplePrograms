/* variable arguments with elipsis operator */

#include<iostream>
#include "exploreme.h"


int myFunction(int n,...)
{
   va_list l_va_list;
   va_start(l_va_list,n);

   while(n > 0)
   {
      printf("\n Values are  :: %d ", va_arg(l_va_list,int) );
      n--;
   }

   va_end(l_va_list);

   return 0;
}

int main()
{
   myFunction(2,5,10);

   return 0;
}
