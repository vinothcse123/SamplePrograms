#include <iostream>
#include <string>
#include <regex>
using std::regex;

int main()
{
    using namespace std;

    std::string s1("VINOTH KUMAR");
    ;

    if (std::regex_match(s1, regex("VIN.*")))
        std::cout << "VIN IS PRESENT\n";

    if (!std::regex_match(s1, regex("VINT.*")))
        std::cout << "VINT IS NOT PRESENT\n";
        
    return 0;
}
