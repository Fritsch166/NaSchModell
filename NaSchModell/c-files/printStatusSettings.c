

#include "..\h-files\naschmodell.h"

const char * const GLOBAL_APC_MODETEXT[4] = {
   "Step1",
   "Step6",
   "Auto6",
   "AutoX"
};

void printStatusSettings(PMODELL pModell)
{
   const short int siX = 2;
   const short int siY = BOARDHEIGHT + MENUHEIGHT + 3;


   //!Prints:

   //! - CARS
   _gotoxy(siX, siY + 0);
   printf("Cars:   %3.1d", pModell->sSettings.iCars);

   //! - VMAX
   _gotoxy(siX, siY + 1);
   printf("VMax:    %2.1d", pModell->sSettings.iVMax);

   //! - P%
   _gotoxy(siX, siY + 2);
   printf("P-DD:   %2.1d%%", pModell->sSettings.iPDDProzent);

   //! - Mode
   _gotoxy(siX, siY + 3);
   printf("Mode: %s", GLOBAL_APC_MODETEXT[pModell->sSettings.eMode]);



   //! - Delayet at v=0
   _gotoxy(siX + 15, siY + 0);
   printf("Increased delay at v=0:  %2.1d%%", pModell->sSettings.iIncreasedDelayAtV0Prozent);

   //! - CruiseControl
   _gotoxy(siX + 15, siY + 1);
   printf("Cruise-control:          %s", (pModell->sSettings.eTCruiseControl == off) ? ("OFF") : (" ON"));

   //! - Save to file
   _gotoxy(siX + 15, siY + 2);
   printf("Save to file:            %s", (pModell->sSettings.eTSaveToFile == off) ? ("OFF") : (" ON"));

   //! - FILEPATH
   _gotoxy(siX + 15, siY + 3);
   int iDiff = 18 - strlen(pModell->sSettings.acFilename);
   if ((iDiff) >= 0)
   {
      printf("-%s[FX.bmp]-", pModell->sSettings.acFilename);
   }
   else
   {
      printf("-%.*s..[FX.bmp]-", 16, pModell->sSettings.acFilename);
   }

   //! - Color Schemes
   _gotoxy(siX, siY + 4);
   printf("Color Schemes: {                           ");
   _gotoxy(siX + 16, siY + 4);
   for (int i = 0, n = 0; i < MAX_COLOR_SCHEMES; i++)
   {
      if (pModell->sSettings.apsCSchemes[i] != NULL)
      {
         if (n != 0)
         {
            printf(",");
         }
         printf("F%d", pModell->sSettings.apsCSchemes[i]->iId);
         n++;
      }
   }
   printf("}");


   //Standard position of the cursor
   _gotoxy(0, 0);
}