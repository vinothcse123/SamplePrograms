#pragma once

#include <iostream>
using namespace std;

namespace TemplateNameSpace
{

   template <class T>
   class TemplateClass
   {
   public:
      T add(T, T);
   };

   template <class T>
   void templateFuncSpecialization(T a);
   template <>
   void templateFuncSpecialization<std::string>(std::string a);

}
#include <TemplateDefinitionFile.tpp> // Good practice to put in end of the header file
