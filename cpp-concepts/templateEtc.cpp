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


class BaseClassWithoutTemplate
{
   public:
   int m_baseClassValue=78;

};

template<typename T>
class DerivedClassWithTemplate : public BaseClassWithoutTemplate
{
    public:
    T m_value;
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

void castTemplateClassToBaseClass()
{
    std::shared_ptr<void> mySharedPtr;

    mySharedPtr.reset(new DerivedClassWithTemplate<int>());

    DerivedClassWithTemplate<int> *intPtr=static_cast<DerivedClassWithTemplate<int>*>(mySharedPtr.get());

    std::cout << "Int "<<  intPtr->m_value  << "==================" << std::endl;

    //Casting to base class

    BaseClassWithoutTemplate *baseClass=static_cast<BaseClassWithoutTemplate*>(mySharedPtr.get());
    std::cout << "baseClass "<<  baseClass->m_baseClassValue  << "==================" << std::endl;

}

int main()
{
    storeTemplateClassInSharedPointerWithDifferentType();

    castTemplateClassToBaseClass();
    

   return 0;
}
