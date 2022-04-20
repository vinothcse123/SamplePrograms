
#include<TemplateHeaderFile.h>
using TemplateNameSpace::TemplateClass;

namespace TemplateNameSpace
{
   template <>
   void templateFuncSpecialization<std::string>(std::string a)
   {
   }
}

int main()
{

   //Creating object as int using template
   TemplateClass <int> int_operation;

   int addition_value=int_operation.add(5,10); 

   return 0;
}
