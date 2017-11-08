


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
   printFrame(0, 0, WINDOWWIDTH + 2, STATUSHEIGHT + BOARDHEIGHT + MENUHEIGHT + 4);
   printFrame(0, MENUHEIGHT + 1, WINDOWWIDTH + 2, BOARDHEIGHT + 2);

   /*

   printBoard(sMyNQueen);
   printStatus(sMyNQueen);

   */

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
         //TODO
         break;

      case OP_CHANGEMODESTATE:
         //TODO
         break;

      case OP_OPENMENUSAVE:
         //TODO
         break;

      case OP_EXIT:
         break;

      default:
         break;
      }

   } while (iOpt != OP_EXIT);

   _clrscr();

   return EXIT_SUCCESS;
}
