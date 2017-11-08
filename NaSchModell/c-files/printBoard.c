
#include "..\h-files\naschmodell.h"

void printBoard(PMODELL pModell, int iView)
{
   short int siXStart = 3;
   short int siYStart = MENUHEIGHT + 2;
   short int siI = 0;
   short int siY = 0;
   short int siX = 0;

   static char acStreet[STREET_LENGTH + 1];

   if (acStreet[0] == 0)
   {
      for (siI = 0; siI < STREET_LENGTH; siI++)
      {
         acStreet[siI] = STREETCHAR;
      }
   }

   for (siI = 0; siI < STREET_LENGTH; siI += PART_STREET_LENGTH)
   {
      siX = (short int)(siI % PART_STREET_LENGTH);
      siY = (short int)(siI / PART_STREET_LENGTH);

      _gotoxy(siXStart + siX, (siYStart + siY * 5) + 2);
      printf("%.*s", PART_STREET_LENGTH, acStreet + siI);
      _gotoxy(siXStart + siX, (siYStart + siY * 5) + 3);
      printf("%.*s", PART_STREET_LENGTH, acStreet + siI);
      _gotoxy(siXStart + siX, (siYStart + siY * 5) + 4);
      printf("%.*s", PART_STREET_LENGTH, acStreet + siI);
   }

   //Standard position of the cursor
   _gotoxy(0, 0);
}