#include<iostream>
#include<string>
#include<vector>
#include<memory>

using std::vector;
using std::cout;
using std::string;
using std::move;

void myFunction(int &a)
{
    cout<< "functionWithLvalue\n";	
}


void myFunction(int &&a)
{
    cout<< "functionWithRvalue\n";	
}


void myFunctionWithoutRvalueVersion(int &a)
{
    cout<< "myFunctionWithoutRvalueVersion\n";	
}

void forwardInCpp()
{
    int a=10;
    


    //[H1]: using forward for named Rvalue : Exisiting rvalue is transferred as rvalue again.
    int &&namedRValue = move(a);

    myFunction(a); // calls myFunction(int &a). NamedRvalue is Lvalue so function with lvalue is called.

    myFunction(std::forward<int>(a)); // calls myFunction(int &&a). NamedRvalue is Lvalue, but since we used forward named rvalue is passed rvalue again.

    //myFunctionWithoutRvalueVersion(std::forward<int>(a)); // Error, because myFunctionWithoutRvalueVersion is not accepting rvalue.  
}

int main()
{
    forwardInCpp();

    return 0;
}
