


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
      if (i < TIMESTAMPLENGTH)
      {
         sModell.sGaugings.acTimeStamp[i] = 0;
      }
   }

   sModell.sGaugings.iTicks = 0;
   sModell.sGaugings.iTrafficJams = 0;
   sModell.sGaugings.runtime = 0;

   initCars(sModell.asCars, sModell.sSettings.iCars);


   //PRINTS-------------------------------------------------------

   _clrscr();
   printFrame(0, 0, WINDOWWIDTH + 2, STATUSHEIGHT + BOARDHEIGHT + MENUHEIGHT + 4);
   printFrame(0, MENUHEIGHT + 1, WINDOWWIDTH + 2, BOARDHEIGHT + 2);
   printFrame(0, BOARDHEIGHT + MENUHEIGHT + 2, STATUS_SETTINGS_WIDTH + 2, STATUSHEIGHT + 2);
   printFrame(STATUS_SETTINGS_WIDTH + 1, BOARDHEIGHT + MENUHEIGHT + 2, STATUS_GAUGINGS_WIDTH + 2, STATUSHEIGHT + 2);

   printBoard(&sModell, 0);
   printStatusSettings(&sModell);
   printStatusGaugings(&sModell);


   _gotoxy(2, 1);
   printf("MENUE                                                            ");
   _gotoxy(2, 2);
   printf("                                                                 ");
   _gotoxy(2, 3);
   printf(" [e] Exit         [m] Toggle Mode  [c] Toggle Cruise-control     ");
   _gotoxy(2, 4);
   printf(" [f] Speichern..  [q] Start..      [d] Toggle Delay_at_v=0       ");

   _gotoxy(0, 0);


   //LOOP---------------------------------------------------------

   do
   {

      iOpt = _getch();

      switch (iOpt)
      {

         case OP_CHANGEMODESTATE:
            if (sModell.sSettings.eMode == step)
            {
               sModell.sSettings.eMode = automatic;
            }
            else
            {
               sModell.sSettings.eMode = step;
            }
            printStatusSettings(&sModell);
            printStatusGaugings(&sModell);
            break;

         case OP_CHANGECRUISECONTROLSTATE:
            if (sModell.sSettings.eTCruiseControl == off)
            {
               sModell.sSettings.eTCruiseControl = on;
            }
            else
            {
               sModell.sSettings.eTCruiseControl = off;
            }
            printStatusSettings(&sModell);
            break;

         case OP_CHANGEDELAYATV0STATE:
            if (sModell.sSettings.eTDelayedAtV0 == off)
            {
               sModell.sSettings.eTDelayedAtV0 = on;
            }
            else
            {
               sModell.sSettings.eTDelayedAtV0 = off;
            }
            printStatusSettings(&sModell);
            break;

         case OP_OPENMENUSAVE:
            //TODO open_menu_save
            break;

         case OP_START:
            //TODO start algo
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
