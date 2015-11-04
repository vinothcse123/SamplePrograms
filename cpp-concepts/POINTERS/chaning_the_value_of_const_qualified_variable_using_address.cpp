#include<iostream>

int myFunction()
{

   return 0;
}

int main()
{
   const int a=12;
   int *p=(int *)&a;

   *p=55;

   printf("\n  *p :: %d ", *p );
   printf("\n  a  :: %d ", a );


   return 0;
}
