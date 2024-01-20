#include <iostream>
#include <memory>
#include <vector>
#include <list>

class Node
{
    public:

    Node()  {}

    int shortestDistance=10000000;//V6P
    std::list<std::pair<int,int>> m_adjNodes;

};


class Graph
{
    public:
    int data=0;
    std::vector<Node> nodeVec;

    Graph(int size)
    {
        nodeVec.resize(size);
    }

    void addEdge(int left,int right,int distance)
    {
        nodeVec[left].m_adjNodes.push_back(std::make_pair(right,distance));
    }

    void depthFirstTraversal(int node)
    {
          
        if(node >= nodeVec.size())
            return;

        for(const auto& childNode : nodeVec[node].m_adjNodes)
        {
            std::cout << " ==============V6P: Key "<<  childNode.first  << "==================" << std::endl;
        }

        for(const auto& childNode : nodeVec[node].m_adjNodes)
        {
            depthFirstTraversal(childNode.first);
        }
    }

    void shortestPathAlgo(int node)
    {
          
        if(node >= nodeVec.size())
            return;

        if(node == 0)
            nodeVec[node].shortestDistance=0;

        for(const auto& childNodePair : nodeVec[node].m_adjNodes)
        {
            std::cout << " ==============V6P: Key "<<  childNodePair.first  << "==================" << std::endl;

            const int& childNodeId = childNodePair.first;
            if(childNodeId == -1)
                continue;

            const int& childNodeDistance = childNodePair.second;
            auto& childNode=nodeVec[childNodeId];

            childNode.shortestDistance = std::min(childNode.shortestDistance,nodeVec[node].shortestDistance+childNodeDistance);
        }

        for(const auto& childNode : nodeVec[node].m_adjNodes)
        {
            if(childNode.first == -1)
                continue;
            shortestPathAlgo(childNode.first);
        }
    }

    void printAllShortestPath()
    {
        int i=0;
        for(const auto& nodeInfo : nodeVec)
        {
             std::cout << " ==============V6P:  "<< i << " : " << nodeInfo.shortestDistance  << "==================" << std::endl;

             i++;
        }
    }
};



int main()
{
    Graph g(5);

    g.addEdge(0,1,10);
    g.addEdge(0,2,20);
    g.addEdge(0,4,5);
    g.addEdge(2,3,40);
    g.addEdge(1,3,5);
    g.addEdge(1,-1,44);
    g.addEdge(3,-1,98);
    g.addEdge(4,3,5);

    // g.depthFirstTraversal(0);

    g.shortestPathAlgo(0);//V6P
    g.printAllShortestPath();
}
