
#include <object_car.h>
#include <stdlib.h>


void initCars(PCAR* apsCars)
{
   for (int i = 0; i < ARRAY_LENGTH; i++)
   {
      apsCars[i] = NULL;
   }
}


PCAR* newCars(PCAR* apsCars, const int iCars)
{
   for (int i = 0; i < ARRAY_LENGTH; i++)
   {
      if (i < iCars)
      {
         //TODO
      }
      else
      {
         apsCars[i] = NULL;
      }
   }

   return (PCAR*)(apsCars);
}


void freeCars(PCAR* apsCars)
{
   for (int i = 0; i < ARRAY_LENGTH; i++)
   {
      if (apsCars[i] != NULL)
      {
         free(apsCars[i]);
         apsCars[i] = NULL;
      }
   }
}

