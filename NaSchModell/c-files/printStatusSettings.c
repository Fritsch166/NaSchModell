

#include "..\h-files\naschmodell.h"

void printStatusSettings(PMODELL pModell)
{
   short int siX = 2;
   short int siY = BOARDHEIGHT + MENUHEIGHT + 3;
   int iDiff = 0;


   //!Prints:

   //! - CARS
   _gotoxy(siX, siY + 0);
   printf("Cars:  %3.1d", pModell->sSettings.iCars);

   //! - VMAX
   _gotoxy(siX, siY + 1);
   printf("VMax:   %2.1d", pModell->sSettings.iVMax);

   //! - P%
   _gotoxy(siX, siY + 2);
   printf("P%%:     %2.1d%%", pModell->sSettings.iPProzent);

   //! - Mode
   _gotoxy(siX, siY + 3);
   printf("Mode: %s", (pModell->sSettings.eMode == step) ? ("Step") : ("Auto"));


   siX += 14;


   //! - Delayet at v=0
   _gotoxy(siX, siY + 0);
   printf("Increased delay at v=0:  %2.1d%%", pModell->sSettings.iIncreasedDelayAtV0Prozent);

   //! - CruiseControl
   _gotoxy(siX, siY + 1);
   printf("Cruise-control: %s", (pModell->sSettings.eTCruiseControl == off) ? ("OFF") : ("ON "));

   //! - Save to file
   _gotoxy(siX, siY + 2);
   printf("Save to file:   %s", (pModell->sSettings.eTSaveToFile == off) ? ("OFF") : ("ON "));

   //! - FILEPATH
   _gotoxy(siX, siY + 3);
   iDiff = strlen(pModell->sSettings.acFilename) - 19;
   if (iDiff < 0) //Print if necesary space
   {
      for (iDiff = -iDiff; iDiff > 0; iDiff--)
      {
         printf(" ");
      }
      iDiff = 0;
   }

   if (iDiff <= 0)
   {
      printf("-%s[.bmp]-", pModell->sSettings.acFilename);
   }
   else
   {
      printf("-%.*s..[.bmp]-", 17, pModell->sSettings.acFilename);
   }


   //Standard position of the cursor
   _gotoxy(0, 0);
}