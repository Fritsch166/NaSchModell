
#include "..\h-files\naschmodell.h"

#include "..\..\common_includes\colormap.h"

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions);

unsigned int GLOBAL_CURSOR_BLINK_RATE = 530;

int main(void)
{

   struct naschmodell sModell;

   {
      char value[12];
      DWORD BufferSize = 12;
      RegGetValue(HKEY_CURRENT_USER, "Control Panel\\Desktop", "CursorBlinkRate", REG_SZ, NULL, (PVOID)&value, &BufferSize);
      GLOBAL_CURSOR_BLINK_RATE = atoi(value);
   }

   initGlobalColorSchemes();
   srand((unsigned int)time(NULL));

   //Initializes the struct and prints the standard GUI-------------

   //Initializes the struct----------------------------------------

   sModell.sSettings.eMode = step1;
   sModell.sSettings.eTSaveToFile = off;
   sModell.sSettings.eTCruiseControl = off;
   sModell.sSettings.iIncreasedDelayAtV0Prozent = 0;
   sModell.sSettings.iCars = 1;
   sModell.sSettings.iPDDProzent = 33;
   sModell.sSettings.iVMax = 5;
   for (int i = 0; i < COMPLPATHLENGTH; i++)
   {
      sModell.sSettings.acFilename[i] = 0;
      sModell.sSettings.acComplFilePath[i] = 0;
      (i < TIMESTAMPLENGTH) ? (sModell.sGaugings.acTimeStamp[i] = 0) : (0);
      (i < MAX_COLOR_SCHEMES) ? (sModell.sSettings.apsCSchemes[i] = NULL) : (0);
   }


   sModell.sGaugings.iTicks = 0;
   sModell.sGaugings.iTotalTrafficJams = 0;
   sModell.sGaugings.iCurrentTrafficJams = 0;
   sModell.sGaugings.runtime = 0;
   sModell.sGaugings.ppsState = (struct saveState **) malloc(sizeof(struct saveState *) * ARRAY_CARS_MAX_LENGTH);
   for (unsigned int iX = 0; iX < ARRAY_CARS_MAX_LENGTH; iX++)
   {
      sModell.sGaugings.ppsState[iX] = (struct saveState *) malloc(sizeof(struct saveState) * MAXTICKS);
   }

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
      iOpt = input(0, 0);

      switch (iOpt)
      {

         case OP_CHANGEMODESTATE:
            switch (sModell.sSettings.eMode)
            {
               case step1:
                  sModell.sSettings.eMode = step6;
                  break;

               case step6:
                  sModell.sSettings.eMode = auto6;
                  break;

               case auto6:
                  sModell.sSettings.eMode = autoX;
                  break;

               default:
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

               //! print data 
               printBoard(&sModell, NULL);
               printStatusGaugings(&sModell);

               //! print menue for simulation
               _gotoxy(2, 1);
               printf("MENUE\\START\\CALCULATION.                                                                  ");
               _gotoxy(2, 2);
               printf("                                                                                          ");
               _gotoxy(2, 3);
               printf(" [e] Exit                    [s] Abort                                                    ");
               _gotoxy(2, 4);
               printf("                                                                                          ");
               if (sModell.sSettings.eTSaveToFile == on)
               {
                  _gotoxy(2, 4);
                  printf(" [p] Abbort and print      ");
               }
               if (sModell.sSettings.eMode == step1 || sModell.sSettings.eMode == step6)
               {
                  _gotoxy(2 + 27, 4);
                  printf("  [LEER] Next..                                         ");
               }
               _gotoxy(0, 0);

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

                //! print board in autox mode at end
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
                     deleteArea(1, 1, WINDOWWIDTH, MENUHEIGHT);
                     _gotoxy(10, 2);
                     printf("Waiting for: Save to file..");
                     printToFile(&sModell);
                     printf("   DONE   [ Press any key to continue ] ");

                     {
                        fseek(stdin, 0, SEEK_END);
                        short int siToggle = 0;
                        while (_kbhit() == 0)
                        {
                           _gotoxy(48 + siToggle * 26, 2);
                           siToggle = (siToggle + 1) % 2;
                           Sleep(GLOBAL_CURSOR_BLINK_RATE);
                        }
                     }

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

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions)
{

   //init array
   for (int iPosition = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      aiPositions[iPosition] = -1;
   }

   //calc random positions
   for (int iN = 0; iN < iAmountPositions;)
   {
      int iPosition = (rand() % STREET_LENGTH);

      if (aiPositions[iPosition] < 0)
      {
         aiPositions[iPosition] = iPosition;
         iN++;
      }
   }

   //Sort psitions at array start
   for (int iPosition = 0, iN = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      if (aiPositions[iPosition] >= 0)
      {
         aiPositions[iN++] = aiPositions[iPosition];
      }
   }
}

void clearKeyboardBuffer(void)
{
   int i;
   while (_kbhit() == 1 && (i = _getch()) != '\n' && i != EOF);
}

int input(const short int siX, const short int siY)
{
   int iKEY_STATE = 0;
   short int siToggle = 0;


   _gotoxy(siX, siY);
   clearKeyboardBuffer();

   while (1)
   {

      iKEY_STATE = GetKeyState(VK_CAPITAL);

      if (0x0001 & iKEY_STATE)
      {
         _gotoxy(150, 4 + MENUHEIGHT + BOARDHEIGHT);
         printf("[ Caps Lock ]");
         do
         {
            _gotoxy(151 + siToggle * 10, 4 + MENUHEIGHT + BOARDHEIGHT);
            siToggle = (siToggle + 1) % 2;
            Sleep(GLOBAL_CURSOR_BLINK_RATE / 2);
            iKEY_STATE = GetKeyState(VK_CAPITAL);
         }
         while (0x0001 & iKEY_STATE);

         _gotoxy(150, 4 + MENUHEIGHT + BOARDHEIGHT);
         printf("             ");
         _gotoxy(siX, siY);
         clearKeyboardBuffer();
      }

      if (_kbhit() == 1)
      {
         int iOpt = _getch();
         clearKeyboardBuffer();
         return iOpt;
      }
   }

}