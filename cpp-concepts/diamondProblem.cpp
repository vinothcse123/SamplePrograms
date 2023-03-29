#include<iostream>
 
 
/*
Assume the following size 
int - 4 bytes
pointer 4 bytes
char 1 byte
*/
 
 
class A
{
    public:
	    int aVar;
};
 
class B : public virtual A
{
		int bVar;
};
 
class C : public virtual  A
{
	int cVar;
};
 
class D : public  B,C
{
public:
	    char dVar;
};


int main()
{
    D d;
    std::cout << sizeof(D) <<std::endl;
    d.aVar=90;
	return 0;
}
