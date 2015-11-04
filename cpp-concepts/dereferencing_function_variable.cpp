#include<iostream>

int myFunction()
{
  printf("\n myFunction");

   return 0;
}

int myFunction2()
{
   printf("\n myFunction2");
   return 0;
}

int myFunction3()
{
   printf("\n myFunction3");

   return 0;
}

int main()
{
   int (*function_variable)() =myFunction;
   (function_variable)();

   function_variable =myFunction2;
   (*function_variable)();

   function_variable =myFunction3;
   (************function_variable)();

   return 0;
}

