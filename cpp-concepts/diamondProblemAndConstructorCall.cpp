#include<iostream>
 
 
/*
Assume the following size 
int - 4 bytes
pointer 4 bytes
char 1 byte
*/
 
 
struct Language
{
	char a;

	Language(int a)
	{

	}

	Language(int a,int b)
	{

	}

	Language(int a,int b,int c)
	{

	}
};
 
struct C : public virtual Language
{
	C():
	Language(100)
	{

	}
		
};
 
struct CPP : public virtual Language
{
	CPP():
	Language(10,20)
	{

	}
};
 
struct Program : C,CPP
{
	Program():
	Language(10,20,30)
	{

	}
};
 

int main()
{
	return 0;
}
