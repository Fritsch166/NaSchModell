
#include "..\h-files\naschmodell.h"

void initCars(ACAR asCars, const int iCars)
{
   for (int i = 0; i < iCars; i++)
   {
      asCars[i].bIsInJam = false;
      asCars[i].iJamGroupId = -1;
      asCars[i].iVChange = 0;

      //TODO randomize cars
      asCars[i].iPosition = i;
      asCars[i].iV = i;


   }
}