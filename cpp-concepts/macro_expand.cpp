#include<iostream>

#define MUL(a,b) a*b
// Here expanded as 5+2*5+1 so, 5+10+1 = 16

int main()
{
   using namespace std;

   int s;

   s=MUL(5+2,5+1);
   // Here not passed  as 10,6 it will passed as 5+2,5+1
   cout<<s<<"\n";



   return 0;
}
