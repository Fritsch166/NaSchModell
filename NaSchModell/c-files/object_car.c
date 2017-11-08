

#include "..\h-files\naschmodell.h"


void disableAllCars(ACAR asCars)
{
   for (int i = 0; i < ARRAY_LENGTH; i++)
   {
      asCars[i].bEnable = false;
   }
}


void enableCars(ACAR asCars, const int iCars)
{
   for (int i = 0; i < ARRAY_LENGTH; i++)
   {
      if (i < iCars)
      {
         //TODO enable Car
      }
      else
      {
         asCars[i].bEnable = false;
      }
   }
}

