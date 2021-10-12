//GH_CPP_CON_9
#include<iostream>
#include<string>
#include<vector>

namespace FirstLevelNamespace
{
    namespace SecondLevelNamespace
    {
       class MyClass
       {

       };

       template<class T>
       class TemplateClass
       {
           T a;
       };
    }
}

//H1:Shorten access to namespace to use FirstLevelNamespace::SecondLevelNamespace::MyClass as SecondLevelNamespace::MyClass

namespace SecondLevelNamespace = FirstLevelNamespace::SecondLevelNamespace;


//H2:All objects of FirstLevelNamespace will be accessed here. This should be avoided in publically exposed API's because pollutes namespace
using namespace FirstLevelNamespace; 


//H3:Here MyClass alone imported from namespace
using FirstLevelNamespace::SecondLevelNamespace::MyClass;

//H4:Alias name for long class name
using MyClassAlias = FirstLevelNamespace::SecondLevelNamespace::MyClass;


//H5:Template alias
template<class T>
using MyTemplateClassAlias = FirstLevelNamespace::SecondLevelNamespace::TemplateClass<T>;

MyTemplateClassAlias<int> myGlobalObj;

int main()
{
    int myNumber=-1;



}
