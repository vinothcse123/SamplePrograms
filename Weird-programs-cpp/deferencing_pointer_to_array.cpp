#include<iostream>


int main()
{
   int a[10]={1,2,3,4,5};

   int (*p)[10]=&a;

   printf("\n  :: %d ", *p[0] );
   printf("\n  :: %d ", **p );


   return 0;
}
