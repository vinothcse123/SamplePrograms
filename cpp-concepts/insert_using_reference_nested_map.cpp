#include<iostream>
#include <map>

int main()
{
   using namespace std;

   map< int,map<int,int> > outer_map;

   outer_map[10].insert(make_pair<int,int>(1,2));
   outer_map[20].insert(make_pair<int,int>(3,4));
   outer_map[20].insert(make_pair<int,int>(5,6));


   map<int,int>  :: iterator in_iter ;
   map<int, map<int,int> > :: iterator out_iter;


   out_iter = outer_map.find(10);

   if(out_iter != outer_map.end())
   {
      printf("\n P");
      printf("\n (out_iter->second).size :: %d ", (out_iter->second).size());
      for(in_iter =  (out_iter->second).begin() ; in_iter != (out_iter->second).end(); in_iter++ )
      {
         printf("\n 1");
      }
   }

   printf("\n out_map.size :: %d ", outer_map.size() );

   map<int,int> ins_test;

   ins_test[20].insert(make_pair<int,int>(5,6));

   printf("\n  :: %d ", ins_test.size() );

   return 0;
}
