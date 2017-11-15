#include "..\h-files\naschmodell.h"

void printMainMenue(void)
{
   _gotoxy(2, 1);
   printf("MENUE                                                                              Autor: Daniel W. Fritsch");
   _gotoxy(2, 2);
   printf("                                                                                   ");
   _gotoxy(2, 3);
   printf(" [e] Exit                    [m] Toggle Mode                                       ");
   _gotoxy(2, 4);
   printf(" [f] Save..                  [q] Start..                 [c] Toggle Cruise-control ");

   _gotoxy(0, 0);

}