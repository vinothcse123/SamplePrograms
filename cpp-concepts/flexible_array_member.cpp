#include<iostream>

int myFunction()
{

   return 0;
}

struct a
{
   int a[];
   char b[];
};


int main()
{
   a obj;

   // obj.a[0]=44; Undefined result

   printf("\n  :: %u ", sizeof(  a ) );


   return 0;
}

