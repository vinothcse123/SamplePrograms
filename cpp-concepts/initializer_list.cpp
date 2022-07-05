#include<iostream>
#include<string>
#include<vector>
#include <initializer_list>

using std::vector;
using std::cout;
using std::string;

class MyClass
{
    int a,b,c;

    MyClass()
    {

    }
};

void demoFunction1(const std::initializer_list<std::string>& initList)
{
    for(std::string initMember : initList)
    {
        std::cout << " ==============V6P: initMember "<<  initMember  << "==================" << std::endl;
    }
    
}

int main()
{
    int myNumber=-1;

    demoFunction1({"1","2","3"});

    cout<< "Result :" << myNumber << '\n';	
    return 0;
}
