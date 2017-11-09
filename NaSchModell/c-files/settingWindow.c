
#include "..\h-files\naschmodell.h"


/*

26x9
**************************
**Cars:**.XX***+/-********
**************************
**Vmax:***.X**************
**************************
**P%:*****.X**************
**************************
**Save Settings? [ENTER]**
**************************

*/

int settingWindow(PMODELL pModell)
{
   short int siX = (WINDOWWIDTH + 2 - (2 + SETTING_WINDOW_WIDTH)) / 2;
   short int siY = MENUHEIGHT + 2 + (BOARDHEIGHT - (2 + SETTING_WINDOW_HEIGHT)) / 2;
   int iOpt = OP_DEFAULT;
   int iState = 0;
   int aiValues[3];

   int aiMINValues[3] = {1, 1, 0};
   int aiMAXValues[3] = {990, 50, 90};


   aiValues[0] = pModell->sSettings.iCars;
   aiValues[1] = pModell->sSettings.iVMax;
   aiValues[2] = pModell->sSettings.iPProzent;

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

   do
   {

      _gotoxy(siX + 3, siY + 2);
      printf("Cars:  %3.1d        ", aiValues[0]);
      _gotoxy(siX + 3, siY + 4);
      printf("VMax:   %2.1d        ", aiValues[1]);
      _gotoxy(siX + 3, siY + 6);
      printf("P%%:     %2.1d        ", aiValues[2]);

      if (iState < 3)
      {
         _gotoxy(siX + 13, siY + 2 + 2 * iState);
         printf("   [+/-]");
         _gotoxy(siX + 13, siY + 2 + 2 * iState);
      }
      else if (iState == 3)
      {
         _gotoxy(siX + 3, siY + 8);
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
            if (iState > 3)
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
   while (iOpt != OP_EXIT && iOpt != OP_STOP && iOpt != OP_SAVESETTINGS);

   if (iOpt == OP_SAVESETTINGS)
   {
      pModell->sSettings.iCars = aiValues[0];
      pModell->sSettings.iVMax = aiValues[1];
      pModell->sSettings.iPProzent = aiValues[2];
   }

   deleteArea(siX, siY, 2 + SETTING_WINDOW_WIDTH, 2 + SETTING_WINDOW_HEIGHT);
  
   return iOpt;
}