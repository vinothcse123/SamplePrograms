//GH_CPP_CON_16 : any.cpp : any and any_cast 

#include <iostream>
#include <string>
#include <vector>
#include <any>

using std::cout;
using std::string;
using std::vector;

int main()
{
    std::any a, b;

    vector<int> vec = {100, 44, 3};
    a = vec;
    vector<string> stringVec = {"asdf3"};
    b = stringVec;

    vector<std::any> anyVec;

    anyVec.push_back(a);
    anyVec.push_back(b);

    for (auto x : std::any_cast<vector<int>>(a))
        cout << "Result :" << x << '\n';
    
    //Taking reference
    vector<int> &referenceToVec = std::any_cast< vector<int>& >(a);

    return 0;
}
