#include "..\h-files\naschmodell.h"

void printToFile(PMODELL pModell)
{

   deleteArea(1, 1, WINDOWWIDTH, MENUHEIGHT);
   _gotoxy(10, 2);
   printf("Waiting for: Save to file..");

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

            int iCarId = pModell->sSettings.iCars - 1;
            struct saveState * psState = &(pModell->sGaugings.ppsState[iCarId][iY]);
            const int iStartPosition = psState->iPosition;
            int iPosition = iStartPosition;

            do
            {

               if (psState->iPosition == iPosition)
               {
                  COLOR pColor = pModell->sSettings.apsCSchemes[iFX]->pf_Converter(psState, &(pModell->sSettings));
                  setColorMap(map, pColor, iY, iPosition);
                  iCarId = (iCarId + 1) % pModell->sSettings.iCars;
                  psState = &(pModell->sGaugings.ppsState[iCarId][iY]);
               }
               else
               {
                  setColorMap(map, Black, iY, iPosition);
               }

               iPosition = (iPosition + 1) % STREET_LENGTH;
            }
            while (iPosition != iStartPosition);
         }


         unsigned int uiLen = strlen(pModell->sSettings.acComplFilePath);
         char * pcFX = pModell->sSettings.acComplFilePath + uiLen - 6;

         sprintf_s(pcFX, 7, "F%d.bmp", pModell->sSettings.apsCSchemes[iFX]->iId);
         drawbmp(pModell->sSettings.acComplFilePath, map->iWidth, map->iHeight, map->ppucRED, map->ppucGREEN, map->ppucBLUE);
         sprintf_s(pcFX, 7, "FX.bmp");
      }
   }

   freeColorMap(map);

   /**************************************************************/

   printf("   DONE   [ Press any key to continue ] ");

   {
      fseek(stdin, 0, SEEK_END);
      short int siToggle = 0;
      while (_kbhit() == 0)
      {
         _gotoxy(48 + siToggle * 26, 2);
         siToggle = (siToggle + 1) % 2;
         Sleep(GLOBAL_CURSOR_BLINK_RATE);
      }
   }
}