#include <iostream>
#include <memory>

struct Node
{

    int m_value;
    std::shared_ptr<Node> next = nullptr;

    Node(int value) : m_value(value)
    {
    }
};



int main()
{
    std::shared_ptr<Node> head(new Node(2));
    head->next.reset(new Node(9));
    head->next->next.reset(new Node(9));

    std::shared_ptr<Node> curNode = head;
    int valueToAdd = 1;
   
    do
    {
        std::cout << curNode->m_value << std::endl;
        curNode = curNode->next;
    } while (curNode != nullptr);

    return 0;
}
