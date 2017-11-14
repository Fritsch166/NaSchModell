


#include "..\h-files\naschmodell.h"

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions);

int main(void)
{
   struct naschmodell sModell;

   //Initializes the struct and prints the standard GUI-------------

   //Initializes the struct----------------------------------------

   srand(time(NULL));

   sModell.sSettings.eMode = step1;
   sModell.sSettings.eTSaveToFile = on;
   sModell.sSettings.eTCruiseControl = off;
   sModell.sSettings.iIncreasedDelayAtV0Prozent = 0;
   sModell.sSettings.iCars = 1;
   sModell.sSettings.iPDDProzent = 33;
   sModell.sSettings.iVMax = 5;
   for (int i = 0; i < COMPLPATHLENGTH; i++)
   {
      sModell.sSettings.acFilename[i] = 0;
      sModell.sSettings.acComplFilePath[i] = 0;
      if (i < TIMESTAMPLENGTH)
      {
         sModell.sGaugings.acTimeStamp[i] = 0;
      }
   }

   sModell.sGaugings.iTicks = 0;
   sModell.sGaugings.iTotalTrafficJams = 0;
   sModell.sGaugings.iCurrentTrafficJams = 0;
   sModell.sGaugings.runtime = 0;


   //init one car
   sModell.asCars[0].bDoDelayAtV0 = false;
   sModell.asCars[0].bIsInJam = false;
   sModell.asCars[0].iJamGroupId = -1;
   sModell.asCars[0].iVChange = 0;
   sModell.asCars[0].iV = rand() % (sModell.sSettings.iVMax + 1);
   sModell.asCars[0].iPosition = 5;



   //PRINTS-------------------------------------------------------

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
      iOpt = _getch();

      switch (iOpt)
      {

         case OP_CHANGEMODESTATE:
            if (sModell.sSettings.eMode == step1)
            {
               sModell.sSettings.eMode = auto6;
            }
            else if (sModell.sSettings.eMode == auto6)
            {
               sModell.sSettings.eMode = step1;
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

         case OP_OPENMENUSAVE:
            //TODO open_menu_save
            break;

         case OP_START:

            //! SettingWindow Start..
            iOpt = settingWindow(&sModell);

            //! print changes settings
            printStatusSettings(&sModell);



            if (iOpt == OP_SAVESETTINGS)
            {
               //! init cars and gaugings

               sModell.sGaugings.iTicks = 0;
               sModell.sGaugings.iTotalTrafficJams = 0;
               sModell.sGaugings.iCurrentTrafficJams = 0;
               sModell.sGaugings.runtime = 0;
               {
                  int aiPositions[STREET_LENGTH];
                  randomize(aiPositions, sModell.sSettings.iCars);
                  for (int i = 0; i < sModell.sSettings.iCars; i++)
                  {

                     sModell.asCars[i].bIsInJam = false;
                     sModell.asCars[i].bDoDelayAtV0 = false;
                     sModell.asCars[i].iJamGroupId = -1;
                     sModell.asCars[i].iVChange = 0;
                     sModell.asCars[i].iV = rand() % (sModell.sSettings.iVMax + 1);
                     sModell.asCars[i].iPosition = aiPositions[i];

                  }
               }
               if (sModell.sSettings.eMode != step1)
               {
                  sModell.sGaugings.runtime = clock();
               }

               //! print data 
               printBoard(&sModell, NULL);
               printStatusGaugings(&sModell);

               _gotoxy(2, 1);
               printf("CALCULATION                                                      ");
               _gotoxy(2, 2);
               printf("                                                                 ");
               _gotoxy(2, 3);
               printf(" [e] Exit                                                        ");
               if (sModell.sSettings.eTSaveToFile == on)
               {
                  _gotoxy(2, 3);
                  printf(" [e] Exit         [p] Abbruch und drucken                        ");
               }
               _gotoxy(2, 4);
               printf(" [s] Abbruch                                                     ");
               if (sModell.sSettings.eMode == step1)
               {
                  _gotoxy(2, 4);
                  printf(" [s] Abbruch      [LEER] Next..                                  ");
               }
               _gotoxy(0, 0);

               iOpt = calcNaSchModell(&sModell);

               if (sModell.sSettings.eTSaveToFile == on)
               {
                  if (iOpt == OP_PRINT || sModell.sGaugings.iTicks >= MAXTICKS)
                  {
                     //TODO print to file
                  }
               }

               printStatusGaugings(&sModell);

               sModell.sGaugings.iTicks = 0;
               sModell.sGaugings.iTotalTrafficJams = 0;
               sModell.sGaugings.iCurrentTrafficJams = 0;
               sModell.sGaugings.runtime = 0;
            }
            else
            {
               printBoard(&sModell, NULL);
            }

            printMainMenue();
            break;

         case OP_EXIT:
            break;

         default:
            break;
      }

   }

   _clrscr();

   return EXIT_SUCCESS;
}

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions)
{
   int iN = 0;
   int iPosition = 0;

   for (iPosition = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      aiPositions[iPosition] = -1;
   }

   for (iN = 0; iN < iAmountPositions;)
   {
      iPosition = (rand() % STREET_LENGTH);

      if (aiPositions[iPosition] < 0)
      {
         aiPositions[iPosition] = iPosition;
         iN++;
      }
   }

   iN = 0;
   for (iPosition = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      if (aiPositions[iPosition] >= 0)
      {
         aiPositions[iN++] = aiPositions[iPosition];
      }
   }

}
