#include<iostream>
#include <exception>


class Divide_by_zero : public std::exception
{
   public:
      const char* what() const throw()
      {
         return "User defined Exception :: Divide by zero !";
      }
};

int main()
{
   using namespace std;
   Divide_by_zero d;

   try
   {
      int i;
      throw d;
   }
   catch(exception e)
   {
      printf("\nException Caught :: %s",e.what());
   }



   return 0;
}
