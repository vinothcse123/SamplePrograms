#include<iostream>
#include<string>
#include<vector>

template<typename T>
T variableTemplateVariable = T(100);

int main()
{

    variableTemplateVariable<int> = 19;
    std::cout<< "variableTemplateVariable<int> :" << variableTemplateVariable<int> << '\n';	

    std::cout<< "variableTemplateVariable<double> :" << variableTemplateVariable<double> << '\n';	

    variableTemplateVariable<double> = 87.78;
    std::cout<< "variableTemplateVariable<double> :" << variableTemplateVariable<double> << '\n';	

    return 0;
}

//Result

// variableTemplateVariable<int> :19
// variableTemplateVariable<double> :100
// variableTemplateVariable<double> :87.78
