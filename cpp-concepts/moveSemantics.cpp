#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

class MoveSemantics
{
    public:

    MoveSemantics& operator=(MoveSemantics&& obj)
    {
         cout<< "Move assignment is called" << '\n';	
          return *this;

    }

   
};

void moveAssignment()
{
    MoveSemantics obj1;
    MoveSemantics obj2;
    obj2=std::move(obj1);
}

int main()
{
    int myNumber=-1;

    moveAssignment();

    cout<< "Result :" << myNumber << '\n';	
    return 0;
}
