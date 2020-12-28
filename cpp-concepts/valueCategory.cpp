#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

void myFunction(int a)
{
}

void lvalueCategory()
{
    
    
    // List of Lvalue Category
    int a=10;
    
}

void rvalueCategory()
{
    int a;
    
    // List of Rvalue Category
    
    myFunction(10);
    myFunction(move(a));
    
}

int main()
{
    int myNumber=-1;
    lvalueCategory();

    cout<< "Result :" << myNumber << '\n';	
    return 0;
}
