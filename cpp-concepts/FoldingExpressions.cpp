#include<iostream>
#include<string>
#include<vector>

template<typename T, typename... Args>
void variadicTemplateDemo(Args&&... args)
{
    std::vector<T> v;
    (v.push_back(args), ...);

    for(int x : v)
        std::cout<< x <<std::endl;
}


int main()
{	
	using namespace std;
    std::vector<int> v;
    variadicTemplateDemo<int>(100,2,34);
	
	return 0;
}
