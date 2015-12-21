#include<iostream>

int main()
{
   using namespace std;
   string str="HAI :: HELLO";
   int pos=0;
   pos=str.find("$",0); // Changes to -1
   printf("\n pos :: %d ", pos );



   return 0;
}
