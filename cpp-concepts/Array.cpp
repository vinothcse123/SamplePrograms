//GH_CPP_CON_3

#include <iostream>


void arrayInitialization()
{
    //All initialized to zero
    int *a=new int[10]();
    int *b=new int[10]{};
    std::cout << "a[0] = " << a[0] << std::endl;

    //First two with 10,20 and rest all are 0
    int *c=new int[10]{10,20};
    std::cout << "c[0] = " << c[0] << std::endl;
    std::cout << "c[3] = " << c[3] << std::endl;

}


void addressRelated()
{

    /* H1 : Address related in array */
    int a, *p;
    p = &a;
    printf("p :: %p \n ", p);
    printf("&p  :: %p \n", &p);
}

void twoDimArray()
{

    /* H2: Two dimensional Array */

    /* S1: Static Allocation of two dimensional array */

    /* Below one is 10 rows and 5 columns */
    int array2d[10][5];

    /* Here column size is 5 and for first two columns of first row is initialized as 10 and 5 and others are zero */

    int dynamicSizeof[][5] = {10, 5};

    std::cout << "dynamicSizeof[0][1] " << dynamicSizeof[0][0] << std::endl;
    std::cout << "dynamicSizeof[1][0] " << dynamicSizeof[1][0] << std::endl;

    //Size of two dimensional array
    std::cout << "sizeof(dynamicSizeof[0]) " << sizeof(dynamicSizeof[0]) << std::endl;

    /* Here second row is initialized */

    //Since second row should be initialized automatically, here  column size is mandatory
    int dualRowInit[][5] = {10, 5, 1, 1, 2, 300, 576, 400};

    std::cout << "dualRowInit[0][1] " << dualRowInit[0][0] << std::endl;
    std::cout << "dualRowInit[1][0] " << dualRowInit[1][0] << std::endl;

    /* initializing row by row for three rows */

    int rowBasedInit[][5] = {{10, 5},
                             {8778, 576, 3, 4, 6},
                             {400}};

    std::cout << "rowBasedInit[0][1] " << rowBasedInit[0][0] << std::endl;
    std::cout << "rowBasedInit[1][0] " << rowBasedInit[1][0] << std::endl;

    /* S2: Dynamic Allocation of two dimensional array */

    const int ROW_COUNT = 10;
    const int COL_COUNT = 5;
    int **twoDimensonArray = new int *[ROW_COUNT];

    for (int i = 0; i < ROW_COUNT; i++)
    {
        //Here, as like static array each row is not continuous with another row
        twoDimensonArray[i] = new int[COL_COUNT];
        *(twoDimensonArray[i]) = i;
    }
}

void multiDimArray()
{
    double ****multiDimArray = nullptr;

    constexpr int32_t dwDim1Size = 10, dwDim2Size = 4, dwDim3Size = 5, dwDim4Size = 5;

    multiDimArray = new double ***[dwDim1Size]{};

    //Allocation of memory

    for (int i = 0; i < dwDim1Size; i++)
    {
        multiDimArray[i] = new double **[dwDim2Size]{};

        for (int j = 0; j < dwDim2Size; j++)
        {
            multiDimArray[i][j] = new double *[dwDim3Size]{};

            for (int k = 0; k < dwDim3Size; k++)
            {
                multiDimArray[i][j][k] = new double[dwDim4Size]{10,20,39};
                std::cout << multiDimArray[i][j][k][3] << " ";

            }
        }
    }

    //Fillvalues

    for (int i = 0; i < dwDim1Size; i++)
    {

        for (int j = 0; j < dwDim2Size; j++)
        {

            for (int k = 0; k < dwDim3Size; k++)
            {
                for (int l = 0; l < dwDim4Size; l++)

                    multiDimArray[i][j][k][l] = l;
            }
        }
    }

    //Print Values
    for (int i = 0; i < dwDim1Size; i++)
    {

        for (int j = 0; j < dwDim2Size; j++)
        {

            for (int k = 0; k < dwDim3Size; k++)
            {
                for (int l = 0; l < dwDim4Size; l++)
                    std::cout << multiDimArray[i][j][k][l] << " ";
            }
        }
        std::cout << std::endl;
    }

    //Destruction of memory
    for (int i = 0; i < dwDim1Size; i++)
    {
        for (int j = 0; j < dwDim2Size; j++)
        {
            for (int k = 0; k < dwDim3Size; k++)
            {
                delete[] multiDimArray[i][j][k];
            }
            delete[] multiDimArray[i][j];
        }
        delete[] multiDimArray[i];
    }

    delete[] multiDimArray;
}

int main()
{
    using namespace std;
    
    arrayInitialization();
    //addressRelated();
    //twoDimArray();
    //multiDimArray();

    return 0;
}
