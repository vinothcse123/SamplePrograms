
#include <iostream>


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

int main()
{  
  manipualteString();
}
