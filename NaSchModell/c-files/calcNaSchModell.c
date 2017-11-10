
#include "..\h-files\naschmodell.h"

int fPrint_NewTick(PMODELL pModell);
int fPrint_Accelerate(PMODELL pModell);
int fPrint_Retard(PMODELL pModell);
int fPrint_DillyDally(PMODELL pModell);
int fPrint_Drive(PMODELL pModell);
int fPrint_TestJam(PMODELL pModell);
int userinteraction(PMODELL pModell);
int fDo_NewTick(PMODELL pModell);
int fDo_Accelerate(PMODELL pModell);
int fDo_Retard(PMODELL pModell);
int fDo_DillyDally(PMODELL pModell);
int fDo_Drive(PMODELL pModell);
int fDo_TestJam(PMODELL pModell);
bool fDo_TestJam_OnOne(PMODELL pModell, int iCarId);

#define FUNC_COUNT 18

int calcNaSchModell(PMODELL pModell)
{
   int iOpt = OP_DEFAULT;
   int iF = 0;
   int(*aFunc[FUNC_COUNT])(PMODELL) =
   {
      fDo_NewTick,
      fPrint_NewTick,
      userinteraction,
      fDo_Accelerate,
      fPrint_Accelerate,
      userinteraction,
      fDo_Retard,
      fPrint_Retard,
      userinteraction,
      fDo_DillyDally,
      fPrint_DillyDally,
      userinteraction,
      fDo_Drive,
      fPrint_Drive,
      userinteraction,
      fDo_TestJam,
      fPrint_TestJam,
      userinteraction
   };

   do
   {
      if (aFunc[iF] != NULL)
      {
         iOpt = aFunc[iF](pModell);
      }

      iF = (int)((iF + 1) % FUNC_COUNT);

      if (iF == 0 && pModell->sGaugings.iTicks >= MAXTICKS)
      {
         iOpt = OP_STOP;
      }
   }
   while (iOpt != OP_EXIT && iOpt != OP_STOP && iOpt != OP_PRINT);

   return iOpt;
}

int userinteraction(PMODELL pModell)
{
   int iOpt = OP_DEFAULT;

   if (pModell->sSettings.eMode == step)
   {
      do
      {
         iOpt = _getch();
      }
      while (iOpt != OP_EXIT && iOpt != OP_STOP && iOpt != OP_STEP && (pModell->sSettings.eTSaveToFile == off || iOpt != OP_PRINT));
   }
   else
   {
      if (_kbhit() == 1)
      {
         iOpt = _getch();

         if (iOpt != OP_EXIT && iOpt != OP_STOP && (pModell->sSettings.eTSaveToFile == off || iOpt != OP_PRINT))
         {
            iOpt = OP_DEFAULT;
         }
      }
   }

   return iOpt;
}

int fPrint_NewTick(PMODELL pModell)
{
   enum states eState = newtick;
   if (pModell->sSettings.eMode == step)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Accelerate(PMODELL pModell)
{
   enum states eState = accelerate;
   if (pModell->sSettings.eMode == step)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Retard(PMODELL pModell)
{
   enum states eState = retard;
   if (pModell->sSettings.eMode == step)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_DillyDally(PMODELL pModell)
{
   enum states eState = dilly_dally;
   if (pModell->sSettings.eMode == step)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Drive(PMODELL pModell)
{
   enum states eState = drive;
   if (pModell->sSettings.eMode == step)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_TestJam(PMODELL pModell)
{
   enum states eState = test_jam;
   if (pModell->sSettings.eMode == step || pModell->sSettings.eMode == automatic)
   {
      printBoard(pModell, &eState);
   }
   printStatusGaugings(pModell);
   return OP_DEFAULT;
}

int fDo_NewTick(PMODELL pModell)
{
   int iCarId = 0;
   PCAR pMyCar = 0;

   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pMyCar = pModell->asCars + iCarId;

      pMyCar->iV = pMyCar->iV + pMyCar->iVChange;
      pMyCar->iVChange = 0;
      if (pModell->sSettings.eTDelayedAtV0 == on && pMyCar->iV + pMyCar->iVChange == 0)
      {
         pMyCar->bDoDelayAtV0 = true;
      }
   }

   return OP_DEFAULT;
}

int fDo_Accelerate(PMODELL pModell)
{
   int iCarId = 0;
   PCAR pMyCar = 0;

   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pMyCar = pModell->asCars + iCarId;

      if (pMyCar->iV + pMyCar->iVChange < pModell->sSettings.iVMax)
      {
         pMyCar->iVChange++;
      }
   }

   return OP_DEFAULT;
}

int fDo_Retard(PMODELL pModell)
{
   int iCarId = 0, iDiff = 0;
   PCAR pMyCar = 0, pCarInfront = 0;

   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pMyCar = pModell->asCars + iCarId;
      pCarInfront = pModell->asCars + ((iCarId + 1) % pModell->sSettings.iCars);

      iDiff = pCarInfront->iPosition - pMyCar->iPosition;
      iDiff += ((iDiff > 0) ? (-1) : (STREET_LENGTH));
      if (pMyCar->iV + pMyCar->iVChange > iDiff)
      {
         pMyCar->iVChange = iDiff - pMyCar->iV;
      }
   }

   return OP_DEFAULT;
}

int fDo_DillyDally(PMODELL pModell)
{
   int iCarId = 0, iRandom = 0;
   PCAR pMyCar = 0;


   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pMyCar = pModell->asCars + iCarId;

      if (pMyCar->iV + pMyCar->iVChange > 0)
      {
         iRandom = rand() % 100;

         if (pModell->sSettings.eTDelayedAtV0 == on && pMyCar->bDoDelayAtV0 == true)
         {
            pMyCar->bDoDelayAtV0 = false;
            if (iRandom < (pModell->sSettings.iPProzent + ((100 - pModell->sSettings.iPProzent) * 30 / 100)))
            {
               pMyCar->iVChange--;
            }
         }
         else if (pModell->sSettings.eTCruiseControl == on && pMyCar->iV + pMyCar->iVChange >= pModell->sSettings.iVMax)
         {
            //Tempomat is on => no dilly_dally
         }
         else if (iRandom < pModell->sSettings.iPProzent)
         {
            pMyCar->iVChange--;
         }
      }
   }

   return OP_DEFAULT;
}


int fDo_Drive(PMODELL pModell)
{
   int iCarId = 0;
   PCAR pMyCar = 0;

   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pMyCar = pModell->asCars + iCarId;

      pMyCar->iPosition = (pMyCar->iPosition + pMyCar->iV + pMyCar->iVChange) % STREET_LENGTH;
   }

   return OP_DEFAULT;
}

int fDo_TestJam(PMODELL pModell)
{
   int iCarId = 0;
   int iCurrentJams = 0;
   int iLastJamGroupId = -1;
   PCAR pCar = 0;

   pModell->sGaugings.iTicks++;

   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      fDo_TestJam_OnOne(pModell, iCarId);
   }

   iLastJamGroupId = pModell->asCars[pModell->sSettings.iCars - 1].iJamGroupId;
   for (iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      pCar = pModell->asCars + iCarId;

      if (pCar->iJamGroupId >= 0)
      {
         if (pCar->iJamGroupId != iLastJamGroupId)
         {
            iCurrentJams++;
            iLastJamGroupId = pCar->iJamGroupId;
         }
      }
   }
   pModell->sGaugings.iCurrentTrafficJams = iCurrentJams;

   return OP_DEFAULT;
}

bool fDo_TestJam_OnOne(PMODELL pModell, int iCarId)
{
   int iDiff = 0, iCarInfrontId = 0;
   PCAR pMyCar = 0, pCarInfront = 0;


   iCarInfrontId = (iCarId + 1) % pModell->sSettings.iCars;
   pMyCar = pModell->asCars + iCarId;
   pCarInfront = pModell->asCars + iCarInfrontId;

   iDiff = pCarInfront->iPosition - pMyCar->iPosition;
   iDiff += ((iDiff > 0) ? (-1) : (STREET_LENGTH));

   if (pMyCar->bIsInJam == true)
   {
      if (pMyCar->iV + pMyCar->iVChange > 0 && pMyCar->iV + pMyCar->iVChange <= iDiff)
      {
         pMyCar->bIsInJam = false;
         pMyCar->iJamGroupId = -1;
      }
   }
   else //bIsInJam == false
   {
      if (pMyCar->iV + pMyCar->iVChange == 0)
      {
         pMyCar->bIsInJam = true;

         if (iDiff <= 1 && fDo_TestJam_OnOne(pModell, iCarInfrontId) == true)
         {
            pMyCar->iJamGroupId = pCarInfront->iJamGroupId;
         }
         else
         {
            pMyCar->iJamGroupId = pModell->sGaugings.iTotalTrafficJams;
            pModell->sGaugings.iTotalTrafficJams++;
         }
      }
      else if (iDiff <= 1)
      {
         if (fDo_TestJam_OnOne(pModell, iCarInfrontId) == true)
         {
            pMyCar->bIsInJam = true;
            pMyCar->iJamGroupId = pCarInfront->iJamGroupId;
         }
         else
         {
            //interessant (:
         }
      }
   }
   return pMyCar->bIsInJam;
}

