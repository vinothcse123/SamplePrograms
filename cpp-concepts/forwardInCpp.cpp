#include<iostream>
#include<string>
#include<vector>
#include<memory>

using std::vector;
using std::cout;
using std::string;
using std::move;



void forwardInCpp()
{
    int a=10;
    


    //[H1]: using forward for named Rvalue : Exisiting rvalue is transferred as rvalue again.
    int &&namedRValue = move(a);

    // int &&namedRValueConvertsToAnotherNamedRvalue = namedRValue; Error because namedRvalue is converted to lvalue internally

    int &&namedRValueConvertsToAnotherNamedRvalue = std::forward<int>(namedRValue); // Ok, because using forward transfer named rvalue as rvalue again.




    //[H2]:using forward for lvalue : lvalue is transferred as lvalue again

    //lvalue is forwarded as lvalue again
    int anotherVariable = std::forward<int>(a); 

    //named rvalue is forwarded as rvalue, but named rvalue is implicitly converted to lvalue again
    int anotherVariable = std::forward<int>(namedRValue); 

}

int main()
{
    int myNumber=-1;
    forwardInCpp();

    cout<< "Result :" << myNumber << '\n';	
    return 0;
}
