
#include <set>
#include <string>
#include <cstdio>

int main()
{
   std::set <std::string> l_set;

   l_set.insert(std::string("HAI"));
   l_set.insert(std::string("HAI"));
   l_set.insert(std::string("HAIiI"));
   l_set.insert(std::string("HAIiI"));
   l_set.insert(std::string("HAIiI"));
   l_set.insert(std::string("HAIiI"));
   l_set.insert(std::string("HAIiI"));
   l_set.insert(std::string("HAIiI"));

   std::set <std::string>::   iterator iter;

   for(iter = l_set.begin(); iter != l_set.end(); iter++)
   {
      printf("\n  :: %s ", (*iter).c_str() );
   }

}
