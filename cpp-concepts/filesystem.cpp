//GH_CPP_CON_14
// Example program
#include <iostream>
#include <string>
#include <filesystem>

int main()
{
 std::filesystem::path obj= "/vinoth/playground/testme/dfd.txt";
  std::cout << "Hello, " << obj.parent_path() << "!\n";

  if(!std::filesystem::exists(obj))
    std::filesystem::create_directory(obj.parent_path()); //add directories based on the object path (without this line it will not work)

  //To create if subfolder is not present
  if(!std::filesystem::exists(obj))
    std::filesystem::create_directories(obj.parent_path()); //add directories based on the object path (without this line it will not work)


}
