
#include<TemplateHeaderFile.h>


int main()
{

   //Creating object as int using template
   TemplateClass <int> int_operation;

   int addition_value=int_operation.add(5,10); 

   return 0;
}
