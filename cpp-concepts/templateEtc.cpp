#include<iostream>
#include<memory>
using std::string;


template <class T>
class TemplateClass 
{
   public:
   T m_value;

   TemplateClass(T value):
   m_value(value)
   {}
};


void storeTemplateClassInSharedPointerWithDifferentType()
{
    std::shared_ptr<void> mySharedPtr;

    mySharedPtr.reset(new TemplateClass<int>(100));

    TemplateClass<int> *intPtr=static_cast<TemplateClass<int>*>(mySharedPtr.get());

    std::cout << "Int "<<  intPtr->m_value  << "==================" << std::endl;


    mySharedPtr.reset(new TemplateClass<string>("HAI"));

    TemplateClass<string> *strPtr=static_cast<TemplateClass<string>*>(mySharedPtr.get());

    std::cout << "string "<<  strPtr->m_value  << "==================" << std::endl;

}

int main()
{
    storeTemplateClassInSharedPointerWithDifferentType();
    

   return 0;
}
