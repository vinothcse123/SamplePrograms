//GH_CPP_CON_4
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::shared_ptr;
using std::string;
using std::vector;
using std::unique_ptr;

#include <iostream>

class BaseClass
{

public:
    BaseClass()
    {
        std::cout << "BaseClass constructor called" << std::endl;
    }

    virtual void myVirtualFunc()
    {
        std::cout << "BaseClass virtual function" << '\n';
    }
};

class DerivedClass : public BaseClass
{

public:
    DerivedClass(int a)
    {
        std::cout << "DerivedClass constructor called" << std::endl;
    }

    virtual void myVirtualFunc()
    {
        std::cout << "DerivedClass virtual function" << '\n';
    }
};

void staticAndDynamicPointerCast()
{
    shared_ptr<BaseClass> baseSharedPtr = std::make_shared<DerivedClass>(100);

    baseSharedPtr->myVirtualFunc();

    //Cannot convert, because targe is not pointer.
    //shared_ptr<DerivedClass> derivedClassPtr = dynamic_cast<shared_ptr<DerivedClass>>(baseSharedPtr);

    //Static cast expects constructor as std::shared_ptr<DerivedClass>::shared_ptr(std::shared_ptr<BaseClass>&) and since it is not possible, it won't allow to convert.
    //shared_ptr<DerivedClass> derivedClassPtr = static_cast<shared_ptr<DerivedClass>>(baseSharedPtr);

    //So, we need static_pointer_cast
    shared_ptr<DerivedClass> derivedClassPtr = std::static_pointer_cast<DerivedClass>(baseSharedPtr);

    shared_ptr<DerivedClass> derivedClassPtrAsDynCast = std::dynamic_pointer_cast<DerivedClass>(baseSharedPtr);


}

void castingForInheritance()
{
    //Pointers

    BaseClass *baseClass;

    //It will just check the type
    DerivedClass *derived=static_cast<DerivedClass*>(baseClass);

    //Reference

    BaseClass baseobj;

    //It expects constructor of type DerivedClass(BaseClass&)
    //DerivedClass &derivedObj=static_cast<DerivedClass>(baseobj);


    //Unique pointer 

    unique_ptr<BaseClass> basePtr(new DerivedClass(222));  

    //Not allowed
   //unique_ptr<DerivedClass> derivedPtr = static_cast< unique_ptr<DerivedClass> >(basePtr);   

   //Not allowed, here  basePtr can point to any type of derived class
   //DerivedClass &derivedClass = *basePtr;




}

int main()
{
    staticAndDynamicPointerCast();
    castingForInheritance();
}
