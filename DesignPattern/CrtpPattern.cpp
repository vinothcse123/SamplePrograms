#include<iostream>

template<typename T>
class BaseClass
{
	
	public:
		void callme()
		{
            			std::cout<<"BaseClass callme called"<<std::endl;

			static_cast<T*>(this)->callme();
		}
};

class DerivedClass : public BaseClass<DerivedClass>
{
	
	public:
		void callme()
		{
			std::cout<<"DerivedClass callme called"<<std::endl;
		}
};

int main()
{
    BaseClass<DerivedClass> *basePtr=new DerivedClass();
    basePtr->callme();

	
	return 0;
}
