#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using std::vector;
using std::cout;
using std::string;
#include <typeinfo>
#include <type_traits>

int myFunction(int a, std::string s,float f,std::string fixedString)
{
    cout<< "myFunction :" << a << " : " << s << " : " << f << " : " << fixedString << '\n';	

}

void bindDemo()
{
    std::function<int(int,std::string,float,std::string)> myCppStyleFuncPtr=myFunction;

    std::function<int(std::string,float)> bindedFunctionPtr =std::bind(myCppStyleFuncPtr,10,std::placeholders::_1,std::placeholders::_2,"FixedString");

    // auto bindedFunctionPtr =std::bind(myCppStyleFuncPtr,10,std::placeholders::_1,std::placeholders::_2,"FixedString");

    bindedFunctionPtr("Hello",90.33);

}

int main()
{

    bindDemo();

    return 0;
}
