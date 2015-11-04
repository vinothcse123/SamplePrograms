#include<iostream>

int myFunction()
{

   return 0;
}

int main()
{
   const int a=10;
   const int b=20;


   int const *  p=&a;
   p=&b;

   int c=10;
   int d=20;
   int *const p2=&c;
//   p2=&d; Cannot be changed
   *p2=55;



   return 0;
}
