#include<iostream>
using namespace std;


template <class T>
class TemplateClass 
{
   public:
      template<typename MFT>
      void templateMemberFunc(MFT a)
      {              

      }

      void templateMemberFuncDefileOutside(T a);
      void templateMemberFuncSpecialization(T a);

};

template <class T>
void TemplateClass<T>::templateMemberFuncDefileOutside(T a)
{

}

template <class T>
void TemplateClass<T>::templateMemberFuncSpecialization(T a)
{

}
template <>
void TemplateClass<std::string>::templateMemberFuncSpecialization(std::string a)
{

}

class NonTemplateClass
{
   public:
      template<typename MFT>
      void memberFunctionTempSpecializationN(MFT a)
      {              

      }
};

// template<typename T>
// void NonTemplateClass<T>::memberFunctionTempSpecializationN<string>(string a)
// {

// }

// void NonTemplateClass::memberFunctionTempSpecializationN<string>(string a)
// {

// }


// template <class c_Type1>
// template <class type1>
// type1 arithmetic_oper<c_Type1> ::  add(type1 a,type1 b)
// {
//    return a+b;
// }


// template <class c_Type1>
// c_Type1 arithmetic_oper<c_Type1> :: sub(c_Type1 a,c_Type1 b)
// {
//    return a-b;
// }

template<class T>
void callMemberFunctionOfUnknownType(T type)
{
    //Here keyword template should be added because T can be any type and we are instructing compiler to ignore validation at compile time.
   type.template add(5,10);
}

void memberFunctionSpecializationOfTemplateClass()
{
    TemplateClass<int> a;
    a.templateMemberFuncDefileOutside(10);
    
}


int main()
{
    memberFunctionSpecializationOfTemplateClass();

   return 0;
}
