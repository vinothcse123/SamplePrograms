/* memory allocation placement new */

#include<iostream>

class test
{
   public:
      int a;
      int operator +(int b)
      {
         printf("\n  :: %d %d", a,b );
         return a+b;
      }

};

int main()
{
   test *buf=new test[10]; // Pre-Allocating the memory
   test t;

   buf = new (buf) test; // Allocating the memory on same memory address which is allocated earlier

   delete []buf;

   return 0;
}
