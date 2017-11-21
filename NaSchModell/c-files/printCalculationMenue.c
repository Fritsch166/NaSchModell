#include "..\h-files\naschmodell.h"

void printCalculationMenue(PMODELL pModell)
{
   _gotoxy(2, 1);
   printf("MENUE\\START\\CALCULATION.                                                                  ");
   _gotoxy(2, 2);
   printf("                                                                                          ");
   _gotoxy(2, 3);
   printf(" [e] Exit                    [s] Abort                                                    ");
   _gotoxy(2, 4);
   printf("                                                                                          ");

   if (pModell->sSettings.eTSaveToFile == on)
   {
      _gotoxy(2, 4);
      printf(" [p] Abbort and print      ");
   }

   if (pModell->sSettings.eMode == step1 || pModell->sSettings.eMode == step6)
   {
      _gotoxy(2 + 27, 4);
      printf("  [LEER] Next..                                         ");
   }

   _gotoxy(0, 0);
}