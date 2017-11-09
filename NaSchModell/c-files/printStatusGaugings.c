

#include "..\h-files\naschmodell.h"

void printStatusGaugings(PMODELL pModell)
{
   short int siX = STATUS_SETTINGS_WIDTH + 3;
   short int siY = BOARDHEIGHT + MENUHEIGHT + 3;
   int iTimeMs = 0;

   //!Prints:

   //! - TICKS
   _gotoxy(siX, siY + 1);
   printf("Ticks:        %3.1d%%        %3.1d", (int)(pModell->sGaugings.iTicks * 100.0 / MAXTICKS), pModell->sGaugings.iTicks);

   //! - VMAX
   _gotoxy(siX, siY + 2);
   printf("Traffic jams:       %9.1d", pModell->sGaugings.iTrafficJams);

   //! - Time


   //! - Time
   _gotoxy(siX, siY + 3);
   if (pModell->sSettings.eMode == automatic)
   {
      if (pModell->sGaugings.runtime != 0)
      {
         if (pModell->sGaugings.iTrafficJams == 0)
         {
            iTimeMs = (int)(clock() - pModell->sGaugings.runtime);
            sprintf_s(pModell->sGaugings.acTimeStamp, TIMESTAMPLENGTH, "Time without jams:   %2.1d,%0.3d", (int)(iTimeMs / CLOCKS_PER_SEC), (int)(iTimeMs % CLOCKS_PER_SEC));
         }

         printf("%s", pModell->sGaugings.acTimeStamp);
      }
      else
      {
         printf("Time without jams:   0,000sec");
      }
   }
   else
   {
      printf("                             ");
   }



   //Standard position of the cursor
   _gotoxy(0, 0);
}