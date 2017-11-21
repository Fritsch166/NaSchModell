
#include "..\h-files\naschmodell.h"

#include "..\..\common_includes\colormap.h"

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions);

unsigned int GLOBAL_CURSOR_BLINK_RATE = 530;


int main(void)
{
   struct naschmodell sModell;

   if (testConsoleSize() < 0)
   {
      return 0;
   }

   initGlobalCursorBlinkRate();
   initGlobalColorSchemes();
   srand((unsigned int)time(NULL));

   //! Initializes the struct

   initModell(&sModell);

   //! print Viewport

   _clrscr();
   printFrame(0, 0, WINDOWWIDTH + 2, STATUSHEIGHT + BOARDHEIGHT + MENUHEIGHT + 4);
   printFrame(0, MENUHEIGHT + 1, WINDOWWIDTH + 2, BOARDHEIGHT + 2);
   printFrame(0, BOARDHEIGHT + MENUHEIGHT + 2, STATUS_SETTINGS_WIDTH + 2, STATUSHEIGHT + 2);
   printFrame(STATUS_SETTINGS_WIDTH + 1, BOARDHEIGHT + MENUHEIGHT + 2, STATUS_GAUGINGS_WIDTH + 2, STATUSHEIGHT + 2);

   printBoard(&sModell, NULL);
   printStatusSettings(&sModell);
   printStatusGaugings(&sModell);
   printMainMenue();


   //LOOP---------------------------------------------------------

   for (int iOpt = OP_DEFAULT; iOpt != OP_EXIT; )
   {
      iOpt = input(0, 0);

      switch (iOpt)
      {

         case OP_OPENMENUSAVE:
            printWindow(&sModell);
            printMainMenue();
            printBoard(&sModell, NULL);
            printStatusSettings(&sModell);
            break;

         case OP_START:

            //! SettingWindow Start..
            iOpt = settingWindow(&sModell);

            //! print changes settings
            printStatusSettings(&sModell);
            printStatusGaugings(&sModell);

            if (iOpt == OP_SAVESETTINGS)
            {
               //! init gaugings
               initCarsAndGaugings(&sModell);

               //! print view port 
               printBoard(&sModell, NULL);
               printStatusGaugings(&sModell);
               printCalculationMenue(&sModell);

               //! if auto mode start timer
               if (sModell.sSettings.eMode == auto6 || sModell.sSettings.eMode == autoX)
               {
                  sModell.sGaugings.runtime = clock();
               }

               /************************************************
                * Start Simulation
                ************************************************/

               iOpt = calcNaSchModell(&sModell);

               /************************************************/

                //! print board one time in autox mode at end
               if (sModell.sGaugings.iTicks >= MAXTICKS && sModell.sSettings.eMode == autoX)
               {
                  const enum states eState = test_jam;
                  printBoard(&sModell, &eState);
               }

               //! print gaugings last time
               printStatusGaugings(&sModell);

               //! safetofile if necessary
               if (sModell.sSettings.eTSaveToFile == on)
               {
                  if (iOpt == OP_PRINT || sModell.sGaugings.iTicks >= MAXTICKS)
                  {
                     printToFile(&sModell);
                  }
               }

               //!reset gaugings
               sModell.sGaugings.iTicks = 0;
               sModell.sGaugings.iTotalTrafficJams = 0;
               sModell.sGaugings.iCurrentTrafficJams = 0;
               sModell.sGaugings.runtime = 0;
            }
            else
            {
               //! print Board after setting abort
               printBoard(&sModell, NULL);
            }

            //!print main menue
            printMainMenue();
            break;

         case OP_EXIT:
            break;

         default:
            break;
      }

   }

   //Release allocated memory
   for (unsigned int iX = 0; iX < ARRAY_CARS_MAX_LENGTH; iX++)
   {
      free(sModell.sGaugings.ppsState[iX]);
      sModell.sGaugings.ppsState[iX] = NULL;
   }
   free(sModell.sGaugings.ppsState);
   sModell.sGaugings.ppsState = NULL;

   //clear window
   _clrscr();

   //EXIT
   return EXIT_SUCCESS;
}