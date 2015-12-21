#include<iostream>
#include <cmath>

int main()
{
   using namespace std;
   int a=100,b=20;

   float f=a-b;
   printf("\n after :: %f ", f );

   f=( (int) (f/60))*a;

   printf("\n  after:: %f ",f  );


   float f2=0.00000000002;

   f2 = floor(f2);


   if(f2)
   {
      printf("\n T");
   }

   int i=(int) 10.99999;

   printf("\n  :: %d ", i );



   return 0;
}
