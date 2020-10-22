#include <iostream>
#include <string>
#include <regex>
using std::regex;

// Regular expression Type: ECMASCRIPT - https://regex101.com/

int main()
{
    using namespace std;

    std::string s1("VINOTH KUMAR");
    ;

    if (std::regex_match(s1, regex("VIN.*")))
        std::cout << "VIN IS PRESENT\n";

    if (!std::regex_match(s1, regex("VINT.*")))
        std::cout << "VINT IS NOT PRESENT\n";

    //Getting position of match

    string s2("VINOTH KUMAR");
    std::smatch m;
    std::regex e("KUMA.*");
    std::regex_search(s2, m, e);

    for (unsigned i = 0; i < m.size(); ++i)
    {
        std::cout << "Value Matched " << m[i] << "\n";
        std::cout << "Pos " << m.position(i) << "\n";
    }

    return 0;
}
