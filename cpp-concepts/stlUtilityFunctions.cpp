//GH_CPP_CON_19

#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

void inserterAndRelated()
{
    std::vector<int> vec{100,200};
    std::vector<int> vecToOverwrite{5,9};   
    std::vector<int> vecToCopy{3,4};
    std::vector<int> vecForBackInserter{8,84};
    std::vector<int>::iterator vecItr=vec.begin();
    std::vector<int>::iterator newValidIter;

    newValidIter = vec.insert(vecItr,10); // Inserting element at beggining pos with value as 10 without allocation and reallocation of memory. Iterator will become invalid because of insertion and valid iterator is returned. The returned iterator will point to same pos as vecItr

    vec.insert(newValidIter,20);// Insert new one using returned iterator. This returned iterator

    std::copy(vecToOverwrite.begin(),vecToOverwrite.end(),vec.begin()+2);// Here the value at 2 position will be overwritten. If value need to be inserted instead of overwriting, we should use inserter.

    std::copy(vecToCopy.begin(),vecToCopy.end(),std::inserter(vec,vec.begin()+3));// Here the value at 3 position will be overwritten. If value need to be inserted instead of overwriting, we should use inserter.

    std::copy(vecForBackInserter.begin(),vecForBackInserter.end(),std::back_inserter(vec));// Here the value at 3 position will be overwritten. If value need to be inserted instead of overwriting, we should use inserter.

    for(const auto& i : vec)
    cout<< "vec :" << i << '\n';	

}

int main()
{

    inserterAndRelated();

    return 0;
}
