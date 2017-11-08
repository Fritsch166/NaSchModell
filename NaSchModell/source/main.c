


#include <naschmodell.h>




int main(void)
{
   struct naschmodell sModell;
   int iOpt = OP_DEFAULT;
   int iN = 0;
   int i = 0;
   short int siX = 0;
   short int siY = 0;


   //Initializes the struct and prints the standard GUI-------------

   //Initializes the struct----------------------------------------


     //TODO


   //PRINTS-------------------------------------------------------


   //Prints the standardGUI
   _clrscr();

   /*
   printFrame(0, 0, WINDOWWIDTH, STATUSHEIGHT + MAXBOARDSIZE + MENUHEIGHT);
   printFrame(0, MENUHEIGHT - 1, WINDOWWIDTH, MAXBOARDSIZE + 2);

   //Prints the Boardframe
   siX = (short int)((WINDOWWIDTH - sMyNQueen.iCurrentSize) / 2) - 1;
   siY = (short int)(MENUHEIGHT + (MAXBOARDSIZE - sMyNQueen.iCurrentSize) / 2) - 1;
   printFrame(siX, siY, sMyNQueen.iCurrentSize + 2, sMyNQueen.iCurrentSize + 2);

   printBoard(sMyNQueen);
   printStatus(sMyNQueen);

   _gotoxy(2, 1);
   printf("MENUE                                          ");
   _gotoxy(2, 2);
   printf("                        [f] Speichermenue      ");
   _gotoxy(2, 3);
   printf(" [+/-] Groesse aendern  [m] Modus aendern      ");
   _gotoxy(2, 4);
   printf(" [e] Exit               [q] Start              ");
   */

   _gotoxy(0, 0);

   //LOOP---------------------------------------------------------

   do
   {

      iOpt = _getch();
      /*
      switch (iOpt) //menu options -> myHeader.h
      {

      case OP_OPENMENUSAVE: //! OP_MENUSAVE
         menuSave(&sMyNQueen);
         printBoard(sMyNQueen);
         printStatus(sMyNQueen);
         break;

      case OP_INKSIZE: //! OP_SIZE++
         iN = sMyNQueen.iCurrentSize + 1;
         if (iN <= MAXBOARDSIZE && iN >= MINBOARDSIZE)
         {
            sMyNQueen.iCurrentSize = iN;

            //New Board Frame
            siX = (short int)((WINDOWWIDTH - iN) / 2) - 1;
            siY = (short int)(MENUHEIGHT + (MAXBOARDSIZE - iN) / 2) - 1;
            printFrame(siX, siY, iN + 2, iN + 2);

            printBoard(sMyNQueen);
            printStatus(sMyNQueen);
         }
         break;

      case OP_DEKSIZE: //! OP_SIZE--
         iN = sMyNQueen.iCurrentSize - 1;
         if (iN <= MAXBOARDSIZE && iN >= MINBOARDSIZE)
         {

            sMyNQueen.iCurrentSize = iN;

            //Clear Bord Area
            siX = (short int)((WINDOWWIDTH - MAXBOARDSIZE) / 2) - 1;
            siY = (short int)(MENUHEIGHT);
            deleteArea(siX, siY, MAXBOARDSIZE + 2, MAXBOARDSIZE);

            //New Board Frame
            siX = (short int)((WINDOWWIDTH - iN) / 2) - 1;
            siY = (short int)(MENUHEIGHT + (MAXBOARDSIZE - iN) / 2) - 1;
            printFrame(siX, siY, iN + 2, iN + 2);

            printBoard(sMyNQueen);
            printStatus(sMyNQueen);
         }
         break;

      case OP_CHANGEMODESTATE: //! OP_CHANGEMODE
         if (sMyNQueen.eMode == step)
         {
            sMyNQueen.eMode = automatic;
         }
         else
         {
            sMyNQueen.eMode = step;
         }
         printStatus(sMyNQueen);
         break;

      case OP_START: //! OP_START
                     //Print calculation Menu
         _gotoxy(2, 1);
         printf("CALCULATION                                    ");
         _gotoxy(2, 2);
         printf("                                               ");
         _gotoxy(2, 3);
         printf("                                               ");
         _gotoxy(2, 3);
         if (sMyNQueen.eMode == step)
         {
            printf(" [LEER] Next                                   ");
         }
         _gotoxy(2, 4);
         printf(" [e] Exit               [s] Abbruch            ");
         //Standard position of the cursor
         _gotoxy(0, 0);

         //Save BoardSize
         if (sMyNQueen.eSave == on)
         {
            saveSol(sMyNQueen.acComplFilePath, sMyNQueen.iSolutions, sMyNQueen.iCurrentSize, sMyNQueen.aiPosQueen, sMyNQueen.acTimeStamp, 1, sMyNQueen.runtime);
         }

         //Get Starttime
         if (sMyNQueen.eMode == automatic)
         {
            sMyNQueen.runtime = clock();
         }

         //Start calculation
         iOpt = calcNQueen(0, &sMyNQueen);

         //SaveTime
         if (sMyNQueen.eSave == on)
         {
            saveSol(sMyNQueen.acComplFilePath, sMyNQueen.iSolutions, sMyNQueen.iCurrentSize, sMyNQueen.aiPosQueen, sMyNQueen.acTimeStamp, 3, sMyNQueen.runtime);
         }

         printBoard(sMyNQueen);
         printStatus(sMyNQueen);

         //ResetSolutions
         sMyNQueen.iSolutions = 0;

         //ResetTime
         sMyNQueen.runtime = 0;

         //Reset Board
         for (i = 0; i < MAXBOARDSIZE; i++)
         {
            sMyNQueen.aiPosQueen[i] = -1;
            sMyNQueen.aiOutput[i] = -1;
         }

         //Print-Standardmenu---------
         _gotoxy(2, 1);
         printf("MENUE                                          ");
         _gotoxy(2, 2);
         printf("                        [f] Speichermenue      ");
         _gotoxy(2, 3);
         printf(" [+/-] Groesse aendern  [m] Modus aendern      ");
         _gotoxy(2, 4);
         printf(" [e] Exit               [q] Start              ");
         break;

      case OP_EXIT: //! OP_EXIT
         break;

      default:
         break;
      } */

   } while (iOpt != OP_EXIT);

   _clrscr();

   return EXIT_SUCCESS;
}
