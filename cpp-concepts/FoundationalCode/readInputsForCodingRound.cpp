
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

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

void readMatrix()
{
    int rowSize=0,columnSize=0;
    
    std::cin >> rowSize >> columnSize;
    
    std::vector<std::vector<int>> matrix;
    
    matrix.resize(rowSize);
    
    for(int i=0;i<rowSize;i++)
        matrix[i].resize(columnSize);
        
    
    for(int i=0;i<rowSize;i++)
    {
        for(int j=0;j<columnSize;j++)
        {
            std::cin >> matrix[i][j];         
        }
        
    }
        
}

void readCommaSeparatedArray()
{
    std::string line;
    std::cin >> line;
    std::string curToken;
    std::stringstream ss(line);
    
    while(std::getline(ss,curToken,','))
    {
        std::cout << curToken << "\n";
    }
    
}

int main()
{  
  //readLinesAsArray();
  //readMatrix();
  readCommaSeparatedArray();
}
