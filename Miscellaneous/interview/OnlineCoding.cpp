//Online challenge  - Read a content

#include<iostream>
#include<sstream> 
#include<vector>
#include<string> 
#include<cstdlib> //atoi

int main()
{
	using namespace std;
	
	//read string from console
	string line;
	getline(cin,line);
	std::cout << "LINE " << line << std::endl;
	
	
	//Parse line and put to container
	string delimiter=" ";
	vector<string> chunks;
	size_t len=0;
	size_t end =0;
	while(end != string::npos)
	{
		end = line.find(delimiter,len);
		chunks.push_back(line.substr(len,end));
		std::cout << line.substr(len,end) << std::endl;				
		len=end+1;		
	}

	
	//Convert string to integer
	vector<int> intChunks;
	for(auto chunk : chunks)
	{
		intChunks.push_back(atoi(chunk.c_str()));
		//stoi can be used too
	}
	
	//Integer to string
	vector<string> intToStringChunks;
	for(auto intElement : intChunks)
	{
		intToStringChunks.push_back(to_string(intElement));
		//stringstream can be used too by calling str()
	}
	
	//Other basic manipulations
	std::string manip="VINOTH KUMAR";
	
	manip.insert(1,"2");
	manip.erase(2,3); 
	manip.substr(1,5);
	manip.append("GANESAN");
	manip.length();
	manip.find("GAN",0);
	
	string concated=manip+string("KARUR");
	
	std::cout<<	manip <<std::endl;
	
}
