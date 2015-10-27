

/* Name Hiding */
#include<iostream>

struct parent
{
   void sameNameFunction()
   {
      printf("\n Parent: Without Parameter");
   }
};

struct child: public parent
{
   void sameNameFunction(int a) // Hiding the name which is used in base class, so name-hiding
   {
      printf("\n Child: With parameter");
   }

   using parent::sameNameFunction;
};

class grantchild : public child
{
   void sameNameFunction(int a,int b)
   {
      printf("\n Grand Child: With parameter");
   }
};


int main()
{
   parent p;
   child c;
   grantchild gc;
   c.sameNameFunction(); // This line will become error when using parent::sameNameFunction; is missed in child clas
   // gc.sameNameFunction(); This will fail since already function named sameNameFunction was there. If sameNameFunction is not there in grand child, call will be allowed


   return 0;
}
