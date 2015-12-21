/*
 * Inline function avoid the functions call. Instead it replaces
 * the function definition inside the code.
 *
 * Inline function is better than macros because macros
 * will not do type check and does not support retun statements
 *
 * Inline  functions should not be used for larger function definition
 * because it lead to larger memory issue when function called several time within a function
 *
 */

inline int max_value(int a,int b)
{
   return (a>b)? a : b;
}

int main()
{
   using namespace std;

   /* Replaced as 5>10 ? 5 : 10; */
   max_value(5,10);

   return 0;
}

