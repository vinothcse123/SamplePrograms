#pragma once


#include<iostream>
using namespace std;

template <class type1>
class TemplateClass 
{
   public:

      type1 add(type1,type1);
};

#include<TemplateDefinitionFile.tpp> // Good practice to put in end of the header file
