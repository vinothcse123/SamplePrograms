#include<iostream>

int main()
{
   using namespace std;

   int i = 0;

   i  |= 0x00000001;
   i  |= 0x00000002;

   printf("\n  :: %X ", i );



   return 0;
}
