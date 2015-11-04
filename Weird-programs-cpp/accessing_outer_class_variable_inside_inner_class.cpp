#include<iostream>

int a;

struct test
{
   int a;
   struct inner
   {
      void callme()
      {
         a=0;
         printf("\n  :: %d ", a );
         printf("\n  :: %d ", ::a );
      }
   };
};

int main()
{

   test::inner obj;
   obj.callme();
   return 0;
}
