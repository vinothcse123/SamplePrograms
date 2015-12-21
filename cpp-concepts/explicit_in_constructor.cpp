#include<iostream>

class class_test
{
   public:
      class_test(int a)
      {
         printf("\n Single paramter called by implicit converstion of compiler! ");
      }
};

class class_test2
{
   public:
      explicit class_test2(int a) // Compiler is restricted for implicit conversion. We explicitly mentioned not to do so!
      {
      }
};

int main()
{
   using namespace std;
   class_test obj = 4;
//   class_test2 obj2= 20; This statement gives the error.

   return 0;
}
