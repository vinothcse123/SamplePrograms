#include<iostream>
#include<string>

//Utility function
template<typename T>
T variadicTemplateDemo(T myVar)
{
    //std::cout << " SINGLE: "<< __PRETTY_FUNCTION__ << "\n";
    std::cout << " SINGLE: " <<myVar<<std::endl;
    return  0;
}

//Variadic template
template<typename T,typename ...VariableArgsType>
T variadicTemplateDemo(T a,VariableArgsType... myVariableArgs)
{
    std::cout << a << "\n";
    //std::cout << " MAIN: "<< __PRETTY_FUNCTION__ << "\n";
    std::cout << variadicTemplateDemo(myVariableArgs...) << std::endl;
    return 99999;
}


int main()
{	
	using namespace std;

    variadicTemplateDemo(5,10,20,909,998);


    //std::cout<< "HELLO" <<std::end;
	
	return 0;
}
