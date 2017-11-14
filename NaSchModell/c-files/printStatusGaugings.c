

#include "..\h-files\naschmodell.h"

void printStatusGaugings(PMODELL pModell)
{
   const short int siX = STATUS_SETTINGS_WIDTH + 3;
   const short int siY = BOARDHEIGHT + MENUHEIGHT + 3;

   //!Prints:

   //! - TICKS
   _gotoxy(siX, siY + 0);
   printf("Ticks:           %3.1d%%     %3.1d", (int)(pModell->sGaugings.iTicks * 100.0 / MAXTICKS), pModell->sGaugings.iTicks);

   //! - Total traffic jams
   _gotoxy(siX, siY + 1);
   printf("Total   traffic jams: %7.1d", pModell->sGaugings.iTotalTrafficJams);

   //! - Current traffic jams
   _gotoxy(siX, siY + 2);
   printf("Current traffic jams: %7.1d", pModell->sGaugings.iCurrentTrafficJams);

   //! - Time
   _gotoxy(siX, siY + 3);
   if (pModell->sSettings.eMode == step1 || pModell->sSettings.eMode == step6)
   {
      printf("                                ");
   }
   else
   {
      if (pModell->sGaugings.runtime != 0)
      {
         if (pModell->sGaugings.iTotalTrafficJams == 0)
         {
            int iTimeMs = (int)(clock() - pModell->sGaugings.runtime);
            sprintf_s(pModell->sGaugings.acTimeStamp, TIMESTAMPLENGTH, "Time    without jams:  %2.1d,%0.3dsec", (int)(iTimeMs / CLOCKS_PER_SEC), (int)(iTimeMs % CLOCKS_PER_SEC));
         }
         printf("%s", pModell->sGaugings.acTimeStamp);
      }
      else
      {
         printf("Time    without jams:   0,000sec");
      }
   }

   //Standard position of the cursor
   _gotoxy(0, 0);
}