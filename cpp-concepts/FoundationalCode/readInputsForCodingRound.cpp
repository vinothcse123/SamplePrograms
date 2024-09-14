// Example program
#include <iostream>
#include <string>
#include <map>
#include <vector>

void readLinesAsArray()
{
    std::vector<int> myVec;
        
    int totalTestCase=0;
    
    std::cin >> totalTestCase;
    
    for(int t=0;t<totalTestCase;t++)
    {
        int arraySize=0,value=0;
        std::cin >> arraySize;
        
        for(int i=0;i<arraySize;i++)
        {
            std::cin >> value;
            myVec.push_back(value);
        }
        
    }
    
}

int main()
{  
  readLinesAsArray();
}
