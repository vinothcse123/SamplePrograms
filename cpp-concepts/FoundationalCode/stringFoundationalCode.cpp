
#include <iostream>


void manipualteString()
{
	std::string manip="VINOTH KUMAR";
	
	manip.insert(1,"2"); 
	std::cout << manip << std::endl;
	manip.erase(2,3); 
	manip.substr(1,5);
	manip.append("GANESAN");
	manip.length();
	manip.find("GAN",0);
	
	std::string concated=manip+std::string("KARUR");
}

int main()
{  
  manipualteString();
}
