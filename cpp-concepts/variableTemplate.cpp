#include<iostream>
#include<string>
#include<vector>

template<typename T>
T piValue = T(3.1415926535897932385);

int main()
{

    std::cout<< "Using Pi as int value :" << piValue<int> << '\n';	
    std::cout<< "Using Pi as int double :" << piValue<double> << '\n';	
    std::cout<< "Using Pi as int float :" << piValue<float> << '\n';	

    return 0;
}
