#pragma once

#include <TemplateHeaderFile.h>

namespace TemplateNameSpace
{
   // Here inline is not required because it is like definition is included in header file with pragma once.

   template <class type1>
   type1 TemplateClass<type1>::add(type1 a, type1 b)
   {
      return a + b;
   }

   template <class T>
   void templateFuncSpecialization(T a)
   {
   }

}
