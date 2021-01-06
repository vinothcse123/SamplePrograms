//GH_CPP_CON_3

#include<iostream>


int main()
{
   using namespace std;

   /* H1 : Address related in array */
   int a,*p;
   p=&a;
   printf("p :: %p \n ", p  );
   printf("&p  :: %p \n",&p  );
   



    /* H2: Two dimensional Array */


   /* S1: Static Allocation of two dimensional array */

   /* Below one is 10 rows and 5 columns */ 
   int array2d[10][5];
    
   /* Here column size is 5 and for first two columns of first row is initialized as 10 and 5 and others are zero */

   int dynamicSizeof[][5]={10,5}; 

   std::cout << "dynamicSizeof[0][1] "<<   dynamicSizeof[0][0]  << std::endl;
   std::cout << "dynamicSizeof[1][0] "<<   dynamicSizeof[1][0]  << std::endl;

   //Size of two dimensional array
   std::cout << "sizeof(dynamicSizeof[0]) "<<   sizeof(dynamicSizeof[0])  << std::endl;


    /* Here second row is initialized */

   //Since second row should be initialized automatically, here  column size is mandatory 
   int dualRowInit[][5]={10,5,1,1,2,300,576,400}; 

   std::cout << "dualRowInit[0][1] "<<   dualRowInit[0][0]  << std::endl;
   std::cout << "dualRowInit[1][0] "<<   dualRowInit[1][0]  << std::endl;

   /* initializing row by row for three rows */

   int rowBasedInit[][5]={ {10,5},
                            {8778,576,3,4,6},
                            {400}}; 

    std::cout << "rowBasedInit[0][1] "<<   rowBasedInit[0][0]  << std::endl;
    std::cout << "rowBasedInit[1][0] "<<   rowBasedInit[1][0]  << std::endl;


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


