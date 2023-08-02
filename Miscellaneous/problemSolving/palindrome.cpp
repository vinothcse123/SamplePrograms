#include<iostream>
#include<string>
#include<vector>
#include <cctype>

using std::vector;
using std::cout;
using std::string;

bool isValidCharacter(int pos)
{
    if((pos >= 65 && pos <=90) || (pos >= 97 && pos <= 122) || (pos >= 48 && pos <= 57))
        return true;
    
    return false;
}

bool isSameLetter(int a,int b)
{
    if((a >= 48 && a <= 57) || ((b >= 48 && b <= 57)))
    {
        return (a == b);
    }
    else if(a == b || a+32 == b || a-32 == b)
        return true;

    return false;
}

bool demoFunction1()
{
    string s="12 2; 1";

    string &myStr=s;
    int i=0,j=myStr.size()-1 ;

    while(i<=j)
    {
        if(!std::isalnum(myStr[i]))
        {
            i--;
            continue;
        }
            
       if(!std::isalnum(myStr[j]))
       {
        j--;
        continue;
        }
            
        if((std::tolower(myStr[i]) != std::tolower(myStr[j])))
        {
            return false;      
        }
        else
        {
            i++;j--;
        }
    }

    return true;
}

int main()
{
    int myNumber=-1;

    cout<< "Result :" << demoFunction1() << '\n';	
    return 0;
}
