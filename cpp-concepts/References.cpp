//GH_CPP_CON_12

#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

struct MyClass
{
    int a=100;
};

MyClass&& localTemporaryobjects()
{
    MyClass obj;

    //Returns Dangling reference as like rvalue reference. No compilation error only warning.
    return std::move(obj);
}


void rvalueReference()
{
    localTemporaryobjects();

}

int main()
{
    rvalueReference();
    	
    return 0;
}
