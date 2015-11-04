#include<iostream>

int myFunction()
{
  printf("\n myFunction");

   return 0;
}


int main()
{
   float (*function_variable)() = (float (*)() )myFunction;
   (function_variable)();

   return 0;
}
