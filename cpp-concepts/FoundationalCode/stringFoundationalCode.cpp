
#include <iostream>
#include <cctype>


void manipualteString()
{
	std::string manip="VINOTHKUMAR";
	
	manip.length();
	
	manip.insert(1,"2"); //V2INOTHKUMAR
	//std::cout << "Insert: " << manip << std::endl;
	
	manip.find("INO",0);
	//std::cout << "Find: " << manip.find("INO",0) << std::endl;
	
	manip.erase(2,3); //V2THKUMAR
	//std::cout << "Erase: " << manip << std::endl;

	manip.substr(1,5);//2THKU
	//std::cout << "Substr: " << manip.substr(1,5) << std::endl; // 2THKU
	
	manip.append("GANESAN");
	
	std::string concated=manip+std::string("KARUR");
	
}

void convertCases()
{
    std::string str= "VINOTH";
    
    for(char &c : str)
    {
        c = std::tolower(c); //cctype and ensure to assign the result value
    }
    
    std::cout << str;
}

bool isAlphaNumericString()
{
     std::string str= "VINOTH123";
     
    for (char c : str) {
        if (!std::isalnum(c)) {
            return false;
        }
    }
    return true;
}

int main()
{  
  //manipualteString();
  //convertCases();
  isAlphaNumericString();
}
