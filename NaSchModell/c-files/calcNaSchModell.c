
#include "..\h-files\naschmodell.h"

int calcNaSchModell(PMODELL pModell)
{
   //TODO algo

   _getch();
   pModell->sGaugings.iTicks++;
   printStatusGaugings(pModell);
   
   _getch();
   pModell->sGaugings.iTicks++;
   printStatusGaugings(pModell);

   _getch();
   pModell->sGaugings.iTicks++;
   pModell->sGaugings.iTrafficJams++;
   printStatusGaugings(pModell);
  
   _getch();
   pModell->sGaugings.iTicks++;
   printStatusGaugings(pModell);

   _getch();
   pModell->sGaugings.iTicks++;
   printStatusGaugings(pModell);



   return 0;
}