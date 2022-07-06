//GH_CPP_CON_15
#include <iostream>
#include <vector>

class MyClass
{
public:
  const int m_arrayLength = 5;

  MyClass()
  {
    ptr2 = new int[m_arrayLength]();
    
    for(int i=0;i<m_arrayLength;i++)
    {
      ptr2[i]=i;
    }
  }

  ~MyClass()
  {
    delete[] ptr2;
  }

  class iteratorVino
  {
  public:
    iteratorVino(int *ptr) : ptr(ptr) {}
    iteratorVino operator++()
    {
      ++ptr;
      return *this;
    }
    bool operator!=(const iteratorVino &other) const { return ptr != other.ptr; }
    const int &operator*() const { return *ptr; }

  private:
    int *ptr;
  };

  int *ptr2;

  iteratorVino begin() const
  {
    return iteratorVino(ptr2);
    ;
  }

  iteratorVino end() const
  {
    return iteratorVino(ptr2 + m_arrayLength);
    ;
  }
};

int main()
{
  MyClass myObj;

  for (auto curObj : myObj)
  {
    std::cout<<"Value " << curObj <<std::endl;
  }

  return 0;
}
