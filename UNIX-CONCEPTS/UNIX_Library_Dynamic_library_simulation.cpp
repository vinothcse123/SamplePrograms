/* UNIX Library Dynamic library simulation */

#include<iostream>
#include "exploreme.h"
#include "dlfcn.h"


int myFunction()
{

   return 0;
}

int main()
{
   void *dynamic_library_open_ptr = dlopen("myDynamicLibrary.so",RTLD_LAZY);


   if(!dynamic_library_open_ptr)
   {
      perror("\nDynamic Library not loaded");
      return -1;
   }

   void *dynamic_library_symbol_ptr = dlsym(dynamic_library_open_ptr,"myFunction");

   if(!dynamic_library_symbol_ptr)
   {
      printf("\n cannot Load myFunction in Dynamic library!!!");
      return -1;
   }


   (*((int(*)())(dynamic_library_symbol_ptr)))();

   return 0;
}


/* Dyanmic Library Code */

/*
 * COMPILATION: g++ -c -fPIC exploreme.cpp
 *
 *
 * LINKING: g++  -shared -o  myDynamicLibrary.so exploreme.o
 *
 * extern "C"
 * {
 *
 * int myFunction()
 * {
 *    printf("\n#######################################   FUNCTION :: %s LINE :: %d \n",__FUNCTION__,__LINE__);
 *
 *       return 0;
 * }
 *
 * }
 *
 */
