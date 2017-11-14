
#include "..\h-files\naschmodell.h"

#define COUNT_VALUES 4

int settingWindow(PMODELL pModell)
{
   const short int siX = (WINDOWWIDTH + 2 - (2 + SETTING_WINDOW_WIDTH)) / 2;
   const short int siY = MENUHEIGHT + 2 + (BOARDHEIGHT - (2 + SETTING_WINDOW_HEIGHT)) / 2;
   int iOpt = OP_DEFAULT;


   int aiValues[COUNT_VALUES];
   const int aiMINValues[COUNT_VALUES] = {1, 1, 0, 0};
   const int aiMAXValues[COUNT_VALUES] = {ARRAY_LENGTH, 50, 90, 90};


   aiValues[0] = pModell->sSettings.iCars;
   aiValues[1] = pModell->sSettings.iVMax;
   aiValues[2] = pModell->sSettings.iPDDProzent;
   aiValues[3] = pModell->sSettings.iIncreasedDelayAtV0Prozent;

   deleteArea(siX, siY, 2 + SETTING_WINDOW_WIDTH, 2 + SETTING_WINDOW_HEIGHT);
   printFrame(siX, siY, 2 + SETTING_WINDOW_WIDTH, 2 + SETTING_WINDOW_HEIGHT);

   _gotoxy(2, 1);
   printf("Start..                                                          ");
   _gotoxy(2, 2);
   printf("                                                                 ");
   _gotoxy(2, 3);
   printf(" [e] Exit                                                        ");
   _gotoxy(2, 4);
   printf(" [s] Abbruch      [ENTER] Next..                                 ");

   _gotoxy(0, 0);

   for (int iState = 0; iOpt != OP_EXIT && iOpt != OP_STOP && iOpt != OP_SAVESETTINGS; )
   {

      _gotoxy(siX + 3, siY + 2);
      printf("Cars:  %3.1d        ", aiValues[0]);
      _gotoxy(siX + 3, siY + 4);
      printf("VMax:   %2.1d        ", aiValues[1]);
      _gotoxy(siX + 3, siY + 6);
      printf("P-DD:  %2.1d%%        ", aiValues[2]);
      _gotoxy(siX + 3, siY + 8);
      printf("IDV0:  %2.1d%%        ", aiValues[3]);

      if (iState < COUNT_VALUES)
      {
         _gotoxy(siX + 13, siY + 2 + 2 * iState);
         printf("   [+/-]");
         _gotoxy(siX + 13, siY + 2 + 2 * iState);
      }
      else if (iState == COUNT_VALUES)
      {
         _gotoxy(siX + 3, siY + 10);
         printf("Save Settings? [ENTER]");
      }

      iOpt = _getch();

      switch (iOpt)
      {


         case OP_INKREMENT:
            if (aiValues[iState] < aiMAXValues[iState])
            {
               aiValues[iState]++;
            }
            break;

         case OP_DEKREMENT:
            if (aiValues[iState] > aiMINValues[iState])
            {
               aiValues[iState]--;
            }
            break;

         case OP_ENTER:
            iState++;
            if (iState > COUNT_VALUES)
            {
               iOpt = OP_SAVESETTINGS;
            }
            break;

         case OP_STOP:
            break;

         case OP_EXIT:
            break;

         default:
            break;
      }
   }


   if (iOpt == OP_SAVESETTINGS)
   {
      pModell->sSettings.iCars = aiValues[0];
      pModell->sSettings.iVMax = aiValues[1];
      pModell->sSettings.iPDDProzent = aiValues[2];
      pModell->sSettings.iIncreasedDelayAtV0Prozent = aiValues[3];
   }

   deleteArea(siX, siY, 2 + SETTING_WINDOW_WIDTH, 2 + SETTING_WINDOW_HEIGHT);

   return iOpt;
}