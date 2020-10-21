#include<iostream>
using namespace std;

template <class type1> 
class TemplateClass; //declaring template

template <class type1>
class TemplateClass 
{
   public:
      type1 variable_name; //Here we can change the datatype
      int fixed_type_int;  //cannot change the datatype

      // Using different type for function template
      template <class F_Type1> F_Type1  add(F_Type1,F_Type1);

      //Using same type as class for function template
      type1 sub(type1,type1);
};


template <class c_Type1>
template <class type1>
type1 TemplateClass<c_Type1> ::  add(type1 a,type1 b)
{
   return a+b;
}



template<class T>
void callMemberFunctionOfUnknownType(T type)
{
    //Here keyword template should be added because T can be any type and we are instructing compiler to ignore validation at compile time.
   type.template add(5,10);
}



int main()
{

   //Creating object as int using template
   TemplateClass <int> int_operation;
   int_operation.variable_name=10;   
   int addition_value=int_operation.add(5,10); 
   addition_value=(int)int_operation.add<int>(5.10,10); // Type casting as int.


   //passing template and calling member function of that
   callMemberFunctionOfUnknownType(int_operation);

   //Pointer to template class
   TemplateClass<int>* ptr=new TemplateClass<int>;

   return 0;
}

