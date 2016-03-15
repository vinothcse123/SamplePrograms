#include<iostream>

struct base
{
   int b:4;
   int c:2;
};



int main()
{
   base b;
   b.b=2;

   printf("\n  :: %d ", b.b );

   return 0;
}
