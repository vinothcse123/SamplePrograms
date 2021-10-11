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

  class iterator
  {
  public:
    iterator(int *ptr) : ptr(ptr) {}
    iterator operator++()
    {
      ++ptr;
      return *this;
    }
    bool operator!=(const iterator &other) const { return ptr != other.ptr; }
    const int &operator*() const { return *ptr; }

  private:
    int *ptr;
  };

  int *ptr2;

  iterator begin() const
  {
    return iterator(ptr2);
    ;
  }

  iterator end() const
  {
    return iterator(ptr2 + m_arrayLength);
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
