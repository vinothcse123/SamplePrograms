#include<iostream>

struct structhack
{
   char a[0];
};

struct no_member_struct
{
};

int main()
{
   printf("\n  :: %u ", sizeof( structhack ) );
   printf("\n  :: %d ", sizeof( no_member_struct ) );
   return 0;
}
