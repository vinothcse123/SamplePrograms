#include<iostream>

int main()
{
   using namespace std;
   int parsed_choice;
   int iter=0;
   string choice="25";
   cout<< choice.substr(iter,1).c_str();

    while((parsed_choice= atoi(choice.substr(iter++,1).c_str())) != 0)
    {
       printf("\n  :: %d ", parsed_choice );
       printf("\n\n11111111111111111111111111111111111  FUNCTION :: %s LINE :: %d \n",__FUNCTION__,__LINE__);
    }



   return 0;
}
