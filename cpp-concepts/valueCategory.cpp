#include<iostream>
#include<string>
#include<vector>
#include<memory>

using std::vector;
using std::cout;
using std::string;
using std::move;

void myFunction(int a)
{
}

void lvalueCategory()
{
    
    
    // List of Lvalue Category

    //1. Variable which is persistent somewhere
    int a=10;
    
}

void rvalueCategory()
{
    int a;
    
    // List of Rvalue Category
    
    //1. Pass by Value
    myFunction(10);

    //2. using move for lvalue
    myFunction(move(a));
    int &&namedRValue = move(a);


    //3. using forward for named rvalue
    // int &&namedRValueConvertsToLvalue = namedRValue; Error because namedRvalue is converted to lvalue internally

    int &&namedRValueConvertsToLvalue = std::forward<int>(namedRValue); // Ok, because using forward transfer named rvalue as rvalue again.

    
}

int main()
{
    int myNumber=-1;
    lvalueCategory();

    cout<< "Result :" << myNumber << '\n';	
    return 0;
}
