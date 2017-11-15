
#include "..\h-files\naschmodell.h"

static const char* const acVelocitys = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char* const apcText[7] =
{
   "NewTick        ",
   "Beschleunigen  ",
   "Bremsen        ",
   "Troedeln       ",
   "Fahren         ",
   "Stau?          ",
   "               "
};

void printBoard(PMODELL pModell, const enum states * pEState)
{
   const short int isXStart = 3;
   const short int isYStart = MENUHEIGHT + 3;


   /**************************************************
    * static values
    **************************************************/
   static char acStreet[STREET_LENGTH + 1];
   if (acStreet[0] == '\0')
   {
      for (int iPosStreet = 0; iPosStreet < STREET_LENGTH; iPosStreet++)
      {
         acStreet[iPosStreet] = STREETCHAR;
      }
   }

   /**************************************************/



   //Street
   for (int iPosStreet = 0; iPosStreet < STREET_LENGTH; iPosStreet += PART_STREET_LENGTH)
   {
      short int siX = (short int)(iPosStreet % PART_STREET_LENGTH);
      short int siY = (short int)(iPosStreet / PART_STREET_LENGTH);

      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 2);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 3);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 4);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 5);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);

   }


   //Cars
   for (int iN = 0; iN < pModell->sSettings.iCars; iN++)
   {

      int iPosStreet = pModell->asCars[iN].iPosition;
      int iVChange = pModell->asCars[iN].iVChange;
      int iTotalVelocity = (pModell->asCars[iN].iV) + iVChange;
      bool bIsInJam = pModell->asCars[iN].bIsInJam;
      int iJamGroupId = pModell->asCars[iN].iJamGroupId;


      short int siX = (short int)(iPosStreet % PART_STREET_LENGTH);
      short int siY = (short int)(iPosStreet / PART_STREET_LENGTH);


      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 2);
      printf("%c", 'A' + (iN % 26));
      _gotoxy(isXStart + siX, (isYStart + siY * 5) + 3);
      printf("%c", acVelocitys[iTotalVelocity]);


      if (pEState != NULL)
      {
         char cCompareV = (iVChange > 0 ? '>' : (iVChange == 0 ? '=' : ('<')));
         switch (*pEState)
         {
            case newtick:
               break;

            case drive:
            case test_jam:
               cCompareV = (iTotalVelocity == 0 ? '!' : cCompareV);

            case accelerate:
            case retard:
            case dilly_dally:
               _gotoxy(isXStart + siX, (isYStart + siY * 5) + 4);
               printf("%c", cCompareV);
               break;

            default:
               ;
         }

         _gotoxy(isXStart, isYStart);
         printf("%s", apcText[*pEState]);

         if (bIsInJam == true)
         {
            _gotoxy(isXStart + siX, (isYStart + siY * 5) + 5);
            printf("%c", 'a' + (iJamGroupId % 26));
         }
      }
      else
      {
         _gotoxy(isXStart, isYStart);
         //Print empty text/last text of array apcText
         printf("%s", apcText[(sizeof(apcText) / sizeof(char*)) - 1]);
      }
   }


   //Standard position of the cursor
   _gotoxy(0, 0);
}