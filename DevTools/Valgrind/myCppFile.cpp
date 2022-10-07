#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

void simpleIntleakFunction()
{
    int *a=new int;
}

void arrayLeakFunction()
{
    double *myDoubleArray=new double[100];
}

int main()
{

    simpleIntleakFunction();
    arrayLeakFunction();

    return 0;
}
