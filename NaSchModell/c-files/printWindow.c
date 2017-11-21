#include "..\h-files\naschmodell.h"

extern unsigned int GLOBAL_CURSOR_BLINK_RATE;

void printWindow(PMODELL pModell)
{
   short int siX = (WINDOWWIDTH - PRINT_WINDOW_WIDTH - 2) / 2;
   short int siY = (MENUHEIGHT + BOARDHEIGHT + STATUSHEIGHT + 4 - PRINT_WINDOW_HEIGHT - 2) / 2;

   //! init locals
   unsigned int iLength = 0;
   char acFilename[COMPLPATHLENGTH + 1];
   enum toggle eTSaveToFile = pModell->sSettings.eTSaveToFile;
   struct colorschemes* apsCSchemes[MAX_COLOR_SCHEMES];
   int iDiff = 0;

   iLength = strlen(pModell->sSettings.acFilename);
   strcpy_s(acFilename, iLength + 1, pModell->sSettings.acFilename);
   memcpy(apsCSchemes, pModell->sSettings.apsCSchemes, MAX_COLOR_SCHEMES * sizeof(struct colorschemes*));

   //! print menu
   _gotoxy(2, 1);
   printf("MENUE\\SETTING_PRINT.                                                                      ");
   _gotoxy(2, 2);
   printf(" [a-z,A-Z,0-9,\\,., ,_,-]     Append                                                       ");
   _gotoxy(2, 3);
   printf(" [Esc] Abort                 [BACKSPACE] Remove          [FX] Toggle Color Schemes        ");
   _gotoxy(2, 4);
   printf(" [>] Toggle ON/OFF           [ENTER] Save..              {                                ");

   _gotoxy(2 + 58, 4);
   for (int i = 0, n = 0; i < MAX_COLOR_SCHEMES; i++)
   {
      if (GLOBAL_ARRAY_COLOR_SCHEMES[i].iId > 0)
      {
         if (n != 0)
         {
            printf(",");
         }
         printf("F%d", GLOBAL_ARRAY_COLOR_SCHEMES[i].iId);
         n++;
      }
   }
   printf("}");

   //!print frame
   deleteArea(siX, siY, PRINT_WINDOW_WIDTH + 2, PRINT_WINDOW_HEIGHT + 2);
   printFrame(siX, siY, PRINT_WINDOW_WIDTH + 2, PRINT_WINDOW_HEIGHT + 2);

   for (int iOpt = 0; iOpt != OP_ESC; )
   {
      /***********************************
       * print locals
       ***********************************/

       //! eTSaveToFile
      _gotoxy(siX + 3, siY + 2);
      printf("Save to file:   %s", (eTSaveToFile == off) ? ("OFF") : (" ON"));

      //!Path/File
      _gotoxy(siX + 3, siY + 4);
      iLength = strlen(acFilename);
      iDiff = 18 - iLength;
      if (iDiff >= 0)
      {
         for (int i = 0; i < iDiff; i++)
         {
            printf("_");
         }
         printf("-%s[FX.bmp]-", acFilename);
      }
      else
      {
         printf("-%s[FX.bmp]-", acFilename - iDiff);
      }

      //! Color Schemes
      _gotoxy(siX + 3, siY + 6);
      printf("Color Schemes:");
      _gotoxy(siX + 3, siY + 7);
      printf("                            ");
      _gotoxy(siX + 3, siY + 7);
      printf("{");
      for (int i = 0, n = 0; i < MAX_COLOR_SCHEMES; i++)
      {
         if (apsCSchemes[i] != NULL)
         {
            if (n != 0)
            {
               printf(",");
            }
            printf("F%d", apsCSchemes[i]->iId);
            n++;
         }
      }
      printf("}");

      /***********************************
      * user input
      ***********************************/
      iOpt = input(siX + 3 + 18, siY + 4);

      switch (iOpt)
      {
         case OP_REMOVE:
            if (iLength > 0)
            {
               iLength--;
               acFilename[iLength] = 0;
            }
            break;

         case OP_CHANGESAVESTATE:
            if (eTSaveToFile == on)
            {
               eTSaveToFile = off;
            }
            else
            {
               eTSaveToFile = on;
            }
            break;

         case OP_ENTER:

            _gotoxy(siX + 3, siY + 9);
            if (eTSaveToFile == on)
            {
               int iNumberOfCSchemes = 0;
               for (int i = 0; i < MAX_COLOR_SCHEMES; i++)
               {
                  if (apsCSchemes[i] != NULL)
                  {
                     iNumberOfCSchemes++;
                  }
               }

               if (iNumberOfCSchemes > 0)
               {
                  char acComplFilePath[COMPLPATHLENGTH + 1];

                  bool bSuccess = true;
                  for (int i = 0; i < MAX_COLOR_SCHEMES && bSuccess == true; i++)
                  {
                     if (apsCSchemes[i] != NULL)
                     {
                        FILE* pFile = NULL;
                        sprintf_s(acComplFilePath, COMPLPATHLENGTH + 1, "%sF%d.bmp", acFilename, apsCSchemes[i]->iId);
                        fopen_s(&pFile, acComplFilePath, "wb");

                        if (pFile == NULL)
                        {
                           bSuccess = false;
                        }
                        else
                        {
                           fclose(pFile);
                        }
                     }
                  }

                  if (bSuccess)
                  {
                     printf("> Erfolgreich Erstellt!");
                     iOpt = OP_ESC;

                     sprintf_s(acComplFilePath, COMPLPATHLENGTH + 1, "%sFX.bmp", acFilename);
                     strcpy_s(pModell->sSettings.acFilename, COMPLPATHLENGTH + 1, acFilename);
                     strcpy_s(pModell->sSettings.acComplFilePath, COMPLPATHLENGTH + 1, acComplFilePath);
                     memcpy(pModell->sSettings.apsCSchemes, apsCSchemes, MAX_COLOR_SCHEMES * sizeof(struct colorschemes*));
                  }
                  else
                  {
                     //Wrong filepath
                     printf("ERROR: Dateipfad!");
                     eTSaveToFile = off;
                  }
               }
               else
               {
                  printf("ERROR: Kein Farbschema!");
                  eTSaveToFile = off;
               }
            }
            else
            {
               iOpt = OP_ESC;
               printf("> Save wurde ausgeschaltet!");
            }

            pModell->sSettings.eTSaveToFile = eTSaveToFile;

            _gotoxy(siX + 3, siY + 10);
            printf("[ Press Any Key to Continue ]");
            {
               fseek(stdin, 0, SEEK_END);
               short int siToggle = 0;
               while (_kbhit() == 0)
               {
                  _gotoxy(siX + 4 + siToggle * 26, siY + 10);
                  siToggle = (siToggle + 1) % 2;
                  Sleep(GLOBAL_CURSOR_BLINK_RATE / 2);
               }
            }

            if (iOpt != OP_ESC)
            {
               deleteArea(siX + 1, siY + 1, PRINT_WINDOW_WIDTH, PRINT_WINDOW_HEIGHT);
            }
            break;

         case OP_ESC:
            break;

         case 0:
            //special keys {F1|F2|F3|F4|..}
            {
               int iFX = 0;

               for (int nVirtKey = VK_F1; iFX == 0 && nVirtKey < VK_F10; nVirtKey++)
               {
                  short int siKEYSTATE = GetKeyState(nVirtKey);
                  iFX = siKEYSTATE & 0x8000 ? (nVirtKey & 0x0F) + 1 : 0;
               }

               if (iFX != 0)
               {
                  if (apsCSchemes[iFX] == NULL && GLOBAL_ARRAY_COLOR_SCHEMES[iFX].iId > 0)
                  {
                     apsCSchemes[iFX] = GLOBAL_ARRAY_COLOR_SCHEMES + iFX;
                  }
                  else
                  {
                     apsCSchemes[iFX] = NULL;
                  }
               }
            }
            break;

         default:
            //filepath append
            if (isalnum(iOpt)
               || iOpt == '\\' || iOpt == '.' || iOpt == ' '
               || iOpt == '_' || iOpt == '-'
               )
            {
               if (iLength < MAXWRITEPATHLENGTH)
               {
                  acFilename[iLength] = (char)(iOpt);
                  iLength++;
                  acFilename[iLength] = 0;
               }
            }

            break;
      }
   }

   deleteArea(siX, siY, PRINT_WINDOW_WIDTH + 2, PRINT_WINDOW_HEIGHT + 2);
}