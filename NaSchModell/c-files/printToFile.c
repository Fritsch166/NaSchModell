#include "..\h-files\naschmodell.h"

void printToFile(PMODELL pModell)
{
 
   /***************Umwandeln in Farbschema*********************

     pModell->sSettings.iCars x pModell->sGaugings.iTicks:
       pModell->sGaugings.ppsState;

     -> pModell->sSettings.apsCSchemes ->

     STREET_LENGTH x MAXTICKS:
     COLORMAP map;

   ************************************************************/

   COLORMAP map = (COLORMAP)malloc(sizeof(struct colormap));

   initColorMap(map, STREET_LENGTH, MAXTICKS);

   //jedes Farbschema
   for (int iFX = 0; iFX < MAX_COLOR_SCHEMES; iFX++)
   {
      if (pModell->sSettings.apsCSchemes[iFX] != NULL)
      {
         
         
         //Daten umwandeln 
         for (int iY = 0; iY < pModell->sGaugings.iTicks; iY++)
         {
            //TODO zeile löschen
            for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
            {

               struct saveState * const psState = &(pModell->sGaugings.ppsState[iCarId][iY]);

               int iX = psState->iPosition;

               COLOR pColor = pModell->sSettings.apsCSchemes[iFX]->pf_Converter(psState, &(pModell->sSettings));

               setColorMap(map, pColor, iY, iX);
            }
         }

         drawbmp(pModell->sSettings.acComplFilePath, map->iWidth, map->iHeight, map->ppucRED, map->ppucGREEN, map->ppucBLUE);
      }
   }

   freeColorMap(map);
}