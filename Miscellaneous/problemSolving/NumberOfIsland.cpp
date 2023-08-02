#include<memory>
#include<iostream>
#include<vector>

void DFS(std::vector<std::vector<int>> matrix,std::vector<std::vector<bool>> &visited,int i,int j,int &islandCount,bool isNewIsland)
{
    if(i < 0 || j< 0 || i >= matrix.size() || j >= matrix[0].size())
        return;

    if(matrix[i][j] == 1 && !visited[i][j])
    {
        visited[i][j]=true;

        if(isNewIsland)
            islandCount++;

        DFS(matrix,visited,i-1,j,islandCount,false);
        DFS(matrix,visited,i-1,j+1,islandCount,false);
        DFS(matrix,visited,i,j+1,islandCount,false);
        DFS(matrix,visited,i+1,j+1,islandCount,false);
        DFS(matrix,visited,i+1,j,islandCount,false);
        DFS(matrix,visited,i+1,j-1,islandCount,false);
        DFS(matrix,visited,i,j-1,islandCount,false);
        DFS(matrix,visited,i-1,j-1,islandCount,false);
    }
}

int main()
{
    std::vector<std::vector<int>> matrix={
                            {1, 1, 0, 0, 0},
                           {1, 1, 0, 0, 0},
                           {0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 1},
        };
    int islandCount=0;

    std::vector<std::vector<bool>> visited;

    for( const auto& row : matrix)
    {
        visited.push_back(std::vector<bool>(row.size(),false));
    }

    for(int i=0;i < matrix.size() ;i++)
    {
        for(int j=0;matrix.size() > 0 && j < matrix[0].size();j++)
        {
            DFS(matrix,visited,i,j,islandCount,true);
        }
    }
    std::cout << " ==============V6P: islandCount "<<  islandCount  << "==================" << std::endl;


    return 0;
}
