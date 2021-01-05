#include<iostream>


int main()
{
   using namespace std;

   /* H1 : Address related in array */
   int a,*p;
   p=&a;
   printf("\n p :: %p ", p  );
   printf("\n &p  :: %p ",&p  );
   



    /* H2: Two dimensional Array */


   /* S1: Static Allocation of two dimensional array */

   /* Below one is 10 rows and 5 columns */ 
   int array2d[10][5];

   int dynamicSizeof[][5]={10,5};


   /* S2: Dynamic Allocation of two dimensional array */
    
    const int ROW_COUNT=10;
    const int COL_COUNT=5;
    int **twoDimensonArray = new int*[ROW_COUNT];

    for(int i=0; i<ROW_COUNT; i++)
    {
        //Here, as like static array each row is not continuous with another row
        twoDimensonArray[i] = new int[COL_COUNT];
        *(twoDimensonArray[i])= i;
    }
   


   return 0;
}



