
#include "..\h-files\naschmodell.h"

static const char* const acVelocitys = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char* apcText[6] =
{
   "NewTick        ",
   "Beschleunigen  ",
   "Bremsen        ",
   "Troedeln       ",
   "Fahren         ",
   "Stau?          "
};

void printBoard(PMODELL pModell, enum states * pEState)
{
   int iXStart = 3;
   int iYStart = MENUHEIGHT + 3;
   int iPosStreet = 0;
   int iY = 0;
   int iX = 0;
   int iN = 0;
   int iTotalVelocity = 0;
   int iVChange = 0;
   char cCompareV = '\0';
   bool bIsInJam = false;
   int iJamGroupId = 0;


   /**************************************************
    * static values
    **************************************************/
   static char acStreet[STREET_LENGTH + 1];


   if (acStreet[0] == 0)
   {
      for (iPosStreet = 0; iPosStreet < STREET_LENGTH; iPosStreet++)
      {
         acStreet[iPosStreet] = STREETCHAR;
      }
   }

   /**************************************************/



   //Street
   for (iPosStreet = 0; iPosStreet < STREET_LENGTH; iPosStreet += PART_STREET_LENGTH)
   {
      iX = (short int)(iPosStreet % PART_STREET_LENGTH);
      iY = (short int)(iPosStreet / PART_STREET_LENGTH);

      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 2);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 3);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 4);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);
      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 5);
      printf("%.*s", PART_STREET_LENGTH, acStreet + iPosStreet);

   }


   //Cars
   for (iN = 0; iN < pModell->sSettings.iCars; iN++)
   {

      iPosStreet = pModell->asCars[iN].iPosition;
      iVChange = pModell->asCars[iN].iVChange;
      iTotalVelocity = (pModell->asCars[iN].iV) + iVChange;
      bIsInJam = pModell->asCars[iN].bIsInJam;
      iJamGroupId = pModell->asCars[iN].iJamGroupId;


      iX = (short int)(iPosStreet % PART_STREET_LENGTH);
      iY = (short int)(iPosStreet / PART_STREET_LENGTH);


      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 2);
      printf("%c", 'A' + (iN % 26));
      _gotoxy(iXStart + iX, (iYStart + iY * 5) + 3);
      printf("%c", acVelocitys[iTotalVelocity]);


      if (pEState != NULL)
      {
         cCompareV = (iVChange > 0 ? '>' : (iVChange == 0 ? '=' : ('<')));
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
               _gotoxy(iXStart + iX, (iYStart + iY * 5) + 4);
               printf("%c", cCompareV);
               break;

            default:
               ;
         }

         _gotoxy(iXStart, iYStart);
         printf("%s", apcText[*pEState]);

         if (bIsInJam == true)
         {
            _gotoxy(iXStart + iX, (iYStart + iY * 5) + 5);
            printf("%c", 'a' + (iJamGroupId % 26));
         }
      }
      else
      {
         _gotoxy(iXStart, iYStart);
         printf("                    ");
      }
   }


   //Standard position of the cursor
   _gotoxy(0, 0);
}