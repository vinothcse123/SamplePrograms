#include<iostream>
using namespace std;

template <class type1> 
class arithmetic_oper; //declaring template

template <class type1>
class arithmetic_oper //defining template
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
type1 arithmetic_oper<c_Type1> ::  add(type1 a,type1 b)
{
   return a+b;
}


template <class c_Type1>
c_Type1 arithmetic_oper<c_Type1> :: sub(c_Type1 a,c_Type1 b)
{
   return a-b;
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
   arithmetic_oper <int> int_operation;
   int_operation.variable_name=10;
   printf("\nUsing a class as a integer :: %d ",int_operation.variable_name);
   int addition_value=int_operation.add(5,10); 
   printf("\nADDITION OF GIVEN VALUE IS %d",addition_value);
   addition_value=(int)int_operation.add<int>(5.10,10); // Type casting as int.
   printf("\nADDITION OF GIVEN VALUE IS with type casting %d",addition_value);


   //Creating object as double using template
   arithmetic_oper <double> double_operation;
   double sub_value=double_operation.sub(50.52,25.02);
   printf("\nSUBTRACTION OF GIVEN VALUE IS %f",sub_value);

   //Creating object as char using template
   arithmetic_oper <char> char_operation;
   char_operation.variable_name='A';
   printf("\nUsing a class as char type :: %c ",char_operation.variable_name);

   //passing template and calling member function of that
   callMemberFunctionOfUnknownType(int_operation);



   return 0;
}
/*
OUTPUT:
Using a class as a integer :: 10 
ADDITION OF GIVEN VALUE IS 15
ADDITION OF GIVEN VALUE IS with type casting 15
SUBTRACTION OF GIVEN VALUE IS 25.500000
Using a class as char type :: A 

*/
