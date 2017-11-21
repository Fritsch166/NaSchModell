#include "..\h-files\naschmodell.h"

void printMainMenue(void)
{
   _gotoxy(2, 1);
   printf("MENUE..                                                                                   ");
   _gotoxy(2, 2);
   printf("                                                                                          ");
   _gotoxy(2, 3);
   printf(" [e] Exit                                                                                 ");
   _gotoxy(2, 4);
   printf(" [f] Save..                  [q] Start..                                                  ");


   _gotoxy(90, 4 + MENUHEIGHT + BOARDHEIGHT);
   printf("Autor: Daniel W. Fritsch");

   _gotoxy(90, 6 + MENUHEIGHT + BOARDHEIGHT);
   printf("V1.02.03");

   _gotoxy(0, 0);

}