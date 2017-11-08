


#include "..\h-files\naschmodell.h"


int main(void)
{
   struct naschmodell sModell;
   int iOpt = OP_DEFAULT;
   int i = 0;


   //Initializes the struct and prints the standard GUI-------------

   //Initializes the struct----------------------------------------


   sModell.sSettings.eMode = step;
   sModell.sSettings.eTSaveToFile = off;
   sModell.sSettings.eTCruiseControl = off;
   sModell.sSettings.eTDelayedAtV0 = off;
   sModell.sSettings.iCars = 10; //TODO remove test value
   sModell.sSettings.iPProzent = 33;
   sModell.sSettings.iVMax = 5;
   for (i = 0; i < COMPLPATHLENGTH; i++)
   {
      sModell.sSettings.acFilename[i] = 0;
      sModell.sSettings.acComplFilePath[i] = 0;
   }

   sModell.sGaugings.iTicks = 0;
   sModell.sGaugings.iTrafficJams = 0;

   initCars(sModell.asCars, sModell.sSettings.iCars);


   //PRINTS-------------------------------------------------------

   _clrscr();
   printFrame(0, 0, WINDOWWIDTH + 2, STATUSHEIGHT + BOARDHEIGHT + MENUHEIGHT + 4);
   printFrame(0, MENUHEIGHT + 1, WINDOWWIDTH + 2, BOARDHEIGHT + 2);
   printFrame(0, BOARDHEIGHT + MENUHEIGHT + 2, STATUS_SETTINGS_WIDTH + 2, STATUSHEIGHT + 2);

   printBoard(&sModell, 0);
   printStatusSettings(&sModell);
   // TODO printStatus(sMyNQueen);


   _gotoxy(2, 1);
   printf("MENUE                                    ");
   _gotoxy(2, 2);
   printf("                                         ");
   _gotoxy(2, 3);
   printf(" [e] Exit         [m] Modus aendern      ");
   _gotoxy(2, 4);
   printf(" [f] Speichern..  [q] Start..            ");

   _gotoxy(0, 0);


   //LOOP---------------------------------------------------------

   do
   {

      iOpt = _getch();

      switch (iOpt)
      {

         case OP_START:
            //TODO start algo
            break;

         case OP_CHANGEMODESTATE:
            //TODO changemode
            break;

         case OP_OPENMENUSAVE:
            //TODO open_menu_save
            break;

         case OP_EXIT:
            break;

         default:
            break;
      }

   }
   while (iOpt != OP_EXIT);

   _clrscr();

   return EXIT_SUCCESS;
}
