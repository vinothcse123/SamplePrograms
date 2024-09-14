
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

int main()
{  
  //readLinesAsArray();
  readMatrix();
}
