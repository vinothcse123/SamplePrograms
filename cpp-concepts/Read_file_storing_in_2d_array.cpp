#include<iostream>
#include<string>
#include <fstream>
#define FILE_NO_OF_COL 50
#define FILE_NO_OF_ROWS 10



bool read_file(char *,char *[][FILE_NO_OF_COL],const char*,int&);

int main()
{
   using namespace std;

   char *file_name="test.xml";
   const char *delimiter=" ";
   char *file_content[FILE_NO_OF_ROWS][FILE_NO_OF_COL];

   int token_count;

   memset(file_content,'\0',sizeof(file_content));

   read_file(file_name,file_content,delimiter,token_count);

   for(int i=0;i<token_count;i++)
      for(int j=0; file_content [i][j] !=NULL ;j++)
      {
         cout<<"\n"<<file_content[i][j];
         printf("\n  :: %s ",file_content[i][j]  );
      }


   return 0;
}

bool read_file(char *p_file_name,char *file_content[FILE_NO_OF_ROWS][FILE_NO_OF_COL],const char *delimiter, int& token
nt )
{
   using namespace std;
   ifstream file_is_obj;
   file_is_obj.open(p_file_name,ios::in);

   string buffer,token;
   int token_pos;
   token_count=0;

   if( file_is_obj.is_open())
   {
      while( !file_is_obj.eof() )
      {
         if(token_count >= FILE_NO_OF_ROWS)
         {
            break;
         }

         buffer.clear();
         token_pos=0;

         std::getline(file_is_obj,buffer);
         for( int iter=0; (unsigned int) token_pos  != string::npos || iter >= FILE_NO_OF_COL ; iter++)
         {
            token.clear();

            token_pos=buffer.find(delimiter,0);
            token=buffer.substr(0,token_pos);
            if( !token.empty() )
            {
               buffer.erase(0,token_pos+strlen(delimiter));

               file_content[token_count][iter] = new char[token.length()+1] ;

               memset(file_content[token_count][iter],'\0',(token.length()+1)*sizeof(char));

               token.copy( file_content[token_count][iter], token.length(), 0);
            }
         }
         token_count++;
      }
   }
   else
   {
      printf("\nFile not found (or) Error in opening the file");
   }

   return true;
}

