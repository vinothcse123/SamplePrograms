
#include<iostream>
#include<string>
#include<tuple>
#include<vector>

//Utility function
template<typename T>
T variadicTemplateFuncDemo(T myVar)
{
    //std::cout << " SINGLE: "<< __PRETTY_FUNCTION__ << "\n";
    std::cout << " variadicTemplateFuncDemo(SingleArgument) : " <<myVar<<std::endl;
    return  0;
}

//Variadic template
template<typename T,typename ...VariableArgsType>
T variadicTemplateFuncDemo(T a,VariableArgsType... myVariableArgs)
{
    std::cout << "VariadicTemplateBeginning..." << a << "\n";
    //std::cout << " MAIN: "<< __PRETTY_FUNCTION__ << "\n";
    
    std::cout << "variadicTemplateFuncDemo(ParameterPack) : "<< variadicTemplateFuncDemo(myVariableArgs...) << std::endl;
    return 99999;
}

template<typename T,typename ...VariableArgsType>
T variadicTemplateFuncStoreInTupleDemo(T a,VariableArgsType... myVariableArgs)
{
    std::tuple<VariableArgsType...> myVariableArgsTuple(myVariableArgs...);
        // std::tuple<Pack...> store( p... );

    std::cout << "variadicTemplateFuncStoreInTupleDemo : "<< std::get<0>(myVariableArgsTuple) << std::endl;

}



//Utility function
template<typename T>
std::vector<T> variadicTemplateFuncStoreInVector(T myVar)
{
    std::vector<T> myIntVector;

    myIntVector.push_back(myVar);

    std::cout << " variadicTemplateFuncStoreInVector(SingleArgument) : " <<myVar<<std::endl;
    return  myIntVector;
}

template<typename T,typename ...VariableArgsType>
std::vector<T> variadicTemplateFuncStoreInVector(T a,VariableArgsType... myVariableArgs)
{
    std::vector<T> myIntVector=variadicTemplateFuncStoreInVector(myVariableArgs...);

    myIntVector.push_back(a);

    return myIntVector;
}

void variadicTemplateFuncStoreInVectorDriver()
{
    variadicTemplateFuncStoreInVector(100000,90909,20,909,998);

    for(auto x : variadicTemplateFuncStoreInVector(100000,90909,20,909,998))
    {
        std::cout << " variadicTemplateFuncStoreInVector(Final) : " <<x<<std::endl;
    }
}

int main()
{	
	using namespace std;

    variadicTemplateFuncDemo(100000,10,20,909,998);

    variadicTemplateFuncStoreInTupleDemo(100000,90909,20,909,998);

	variadicTemplateFuncStoreInVectorDriver();

	return 0;
}
