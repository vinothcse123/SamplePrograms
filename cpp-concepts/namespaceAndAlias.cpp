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
    }
}

//Shorten access to namespace to use FirstLevelNamespace::SecondLevelNamespace::MyClass as SecondLevelNamespace::MyClass

namespace SecondLevelNamespace = FirstLevelNamespace::SecondLevelNamespace;


//All objects of FirstLevelNamespace will be accessed here. This should be avoided in publically exposed API's because pollutes namespace
using namespace FirstLevelNamespace; 


//Here MyClass alone imported from namespace
using FirstLevelNamespace::SecondLevelNamespace::MyClass;


int main()
{
    int myNumber=-1;


}
