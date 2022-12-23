#include<iostream>
#include<string>
#include<vector>
#include<memory>

using std::vector;
using std::cout;
using std::string;
using std::move;

class MyClass
{
    public:
    int a=100;

};

MyClass myFunction(int a)
{
    return MyClass();
}

MyClass getObject()
{
    MyClass obj;
    return obj;
}

void lvalueCategory()
{
    int x=10; // Here subexpression x is lvalue because address of x can be taken.

    //1. Expression whose address can be taken
    "Hai Hello"; // This literal is stored somewhere in static location, so lvalue. Normally in code we will get starting address of this.
    ++x; // Here after expression address can be taken, it is lvalue.

    //2. If expression has some identity, then it is lvalue
    int a=10,*b=nullptr;
    int &aRef=a;
}

void prvalueCategory()
{
    int a=10,x=20;
    double d=100.8;
    MyClass obj;
    int &&namedRValue = move(a); 

    // List of Rvalue Category
    
    //1. Expression where address cannot be taken in prvalue 
    10;
    89.7987;
    getObject(); // All return values which are not reference is prvalue
    static_cast<double>(x);  // After cast address cannot be taken
    std::string(); // No address
    throw std::exception();
    a+d; // After expression identity cannot be taken


    
    //3. using forward for named rvalue
    // int &&namedRValueConvertsToLvalue = namedRValue; Error because namedRvalue is converted to lvalue internally

    int &&namedRValueConvertsToLvalue = std::forward<int>(namedRValue); // Ok, because using forward transfer named rvalue as rvalue again.

    //4. simple this statement is rvalue because this is not variable
    // this; //this is prvalue
    
}


MyClass&& functionReturningRValueRef(MyClass &obj)
{
    return std::move(obj);   
}


void xvalueCategory()
{
    MyClass obj;

    //Here obj is nearing end of its lifetime.
    MyClass&& obj2=functionReturningRValueRef(obj);

    //At this point obj is in valid state but accessing it will cause undefined behaviour

    MyClass moveObj;
    MyClass moveObj2=std::move(moveObj);//Here moveObj is xvalue

    static_cast<MyClass&&>(obj);

}

void rvalueCategory()
{
    // 1. All rvalues are prvalue
    MyClass obj2= getObject();

    //2. All temporaries which are xvalue is rvalue catetory

}


int main()
{
    lvalueCategory();
    prvalueCategory();
    xvalueCategory();
    rvalueCategory();
    
    return 0;
}
