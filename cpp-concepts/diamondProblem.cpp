#include<iostream>
 
 
/*
Assume the following size 
int - 4 bytes
pointer 4 bytes
char 1 byte
*/
 
 
class Language
{
	char a;
};
 
class C : public Language
{
		
};
 
class CPP : public Language
{
	
};
 
class Program : C,CPP
{
	
};
 

int main()
{
	return 0;
}
