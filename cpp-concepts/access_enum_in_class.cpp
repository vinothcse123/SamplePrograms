#include<iostream>

struct test
{
   enum op
   {
      mytrue,
      myfalse,
   };

};
int main()
{

   printf("\n  :: %d ", test::myfalse );


   return 0;
}
