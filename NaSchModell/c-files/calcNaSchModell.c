
#include "..\h-files\naschmodell.h"

int fPrint_NewTick(PMODELL pModell);
int fPrint_Accelerate(PMODELL pModell);
int fPrint_Retard(PMODELL pModell);
int fPrint_DillyDally(PMODELL pModell);
int fPrint_Drive(PMODELL pModell);
int fPrint_TestJam(PMODELL pModell);
int userinteractionSTEP1(PMODELL pModell);
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
   int(*aFunc[FUNC_COUNT])(PMODELL) =
   {
      fDo_NewTick,
      fPrint_NewTick,
      userinteractionSTEP1,
      fDo_Accelerate,
      fPrint_Accelerate,
      userinteractionSTEP1,
      fDo_Retard,
      fPrint_Retard,
      userinteractionSTEP1,
      fDo_DillyDally,
      fPrint_DillyDally,
      userinteractionSTEP1,
      fDo_Drive,
      fPrint_Drive,
      userinteractionSTEP1,
      fDo_TestJam,
      fPrint_TestJam,
      userinteraction
   };

   for (int iF = 0; iOpt != OP_EXIT && iOpt != OP_STOP && iOpt != OP_PRINT; iF++, iF %= FUNC_COUNT)
   {
      iOpt = aFunc[iF](pModell);

      if (iF == FUNC_COUNT - 1 && pModell->sGaugings.iTicks >= MAXTICKS)
      {
         iOpt = OP_STOP;
      }
   }

   return iOpt;
}

int userinteractionSTEP1(PMODELL pModell)
{
   int iOpt = OP_DEFAULT;

   if (pModell->sSettings.eMode == step1)
   {
      do
      {
         iOpt = _getch();
      }
      while (iOpt != OP_EXIT
         && iOpt != OP_STOP
         && iOpt != OP_STEP
         && (pModell->sSettings.eTSaveToFile == off || iOpt != OP_PRINT));
   }

   return iOpt;
}

int userinteraction(PMODELL pModell)
{
   int iOpt = OP_DEFAULT;

   if (pModell->sSettings.eMode == step1 || pModell->sSettings.eMode == step6)
   {
      do
      {
         iOpt = _getch();
      }
      while (iOpt != OP_EXIT
         && iOpt != OP_STOP
         && iOpt != OP_STEP
         && (pModell->sSettings.eTSaveToFile == off || iOpt != OP_PRINT));
   }
   else
   {
      if (_kbhit() == 1)
      {
         iOpt = _getch();

         if (iOpt != OP_EXIT
            && iOpt != OP_STOP
            && (pModell->sSettings.eTSaveToFile == off || iOpt != OP_PRINT))
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
   if (pModell->sSettings.eMode == step1)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Accelerate(PMODELL pModell)
{
   enum states eState = accelerate;
   if (pModell->sSettings.eMode == step1)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Retard(PMODELL pModell)
{
   enum states eState = retard;
   if (pModell->sSettings.eMode == step1)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_DillyDally(PMODELL pModell)
{
   enum states eState = dilly_dally;
   if (pModell->sSettings.eMode == step1)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_Drive(PMODELL pModell)
{
   enum states eState = drive;
   if (pModell->sSettings.eMode == step1)
   {
      printBoard(pModell, &eState);
   }
   return OP_DEFAULT;
}

int fPrint_TestJam(PMODELL pModell)
{
   enum states eState = test_jam;
   if (pModell->sSettings.eMode != autoX)
   {
      printBoard(pModell, &eState);
   }
   printStatusGaugings(pModell);
   return OP_DEFAULT;
}

int fDo_NewTick(PMODELL pModell)
{
   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      PCAR pMyCar = pModell->asCars + iCarId;

      pMyCar->iV = pMyCar->iV + pMyCar->iVChange;
      pMyCar->iVChange = 0;
      if (pModell->sSettings.iIncreasedDelayAtV0Prozent > 0 && pMyCar->iV + pMyCar->iVChange == 0)
      {
         pMyCar->bDoDelayAtV0 = true;
      }
   }

   return OP_DEFAULT;
}

int fDo_Accelerate(PMODELL pModell)
{
   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      PCAR pMyCar = pModell->asCars + iCarId;

      if (pMyCar->iV + pMyCar->iVChange < pModell->sSettings.iVMax)
      {
         pMyCar->iVChange++;
      }
   }

   return OP_DEFAULT;
}

int fDo_Retard(PMODELL pModell)
{
   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      PCAR pMyCar = pModell->asCars + iCarId;
      PCAR pCarInfront = pModell->asCars + ((iCarId + 1) % pModell->sSettings.iCars);
      int iDiff = pCarInfront->iPosition - pMyCar->iPosition;
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
   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      PCAR pMyCar = pModell->asCars + iCarId;

      if (pMyCar->iV + pMyCar->iVChange > 0)
      {
         int iRandom = rand() % 100;

         if (pModell->sSettings.iIncreasedDelayAtV0Prozent > 0 && pMyCar->bDoDelayAtV0 == true)
         {
            pMyCar->bDoDelayAtV0 = false;
            if (iRandom < (pModell->sSettings.iPDDProzent + ((100 - pModell->sSettings.iPDDProzent) * pModell->sSettings.iIncreasedDelayAtV0Prozent / 100)))
            {
               pMyCar->iVChange--;
            }
         }
         else if (pModell->sSettings.eTCruiseControl == on && pMyCar->iV + pMyCar->iVChange >= pModell->sSettings.iVMax)
         {
            //Tempomat is on => no dilly_dally
         }
         else if (iRandom < pModell->sSettings.iPDDProzent)
         {
            pMyCar->iVChange--;
         }
      }
   }

   return OP_DEFAULT;
}


int fDo_Drive(PMODELL pModell)
{
   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      PCAR  pMyCar = pModell->asCars + iCarId;

      pMyCar->iPosition = (pMyCar->iPosition + pMyCar->iV + pMyCar->iVChange) % STREET_LENGTH;
   }

   return OP_DEFAULT;
}

int fDo_TestJam(PMODELL pModell)
{
   pModell->sGaugings.iTicks++;

   for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
   {
      fDo_TestJam_OnOne(pModell, iCarId);
   }

   {
      pModell->sGaugings.iCurrentTrafficJams = 0;
      int iLastJamGroupId = pModell->asCars[pModell->sSettings.iCars - 1].iJamGroupId;
      for (int iCarId = 0; iCarId < pModell->sSettings.iCars; iCarId++)
      {
         PCAR pCar = pModell->asCars + iCarId;

         if (pCar->bIsInJam == true)
         {
            if (pCar->iJamGroupId != iLastJamGroupId)
            {
               pModell->sGaugings.iCurrentTrafficJams++;
               iLastJamGroupId = pCar->iJamGroupId;
            }
         }
      }

   }

   return OP_DEFAULT;
}

bool fDo_TestJam_OnOne(PMODELL pModell, int iCarId)
{
   int iCarInfrontId = (iCarId + 1) % pModell->sSettings.iCars;
   PCAR pMyCar = pModell->asCars + iCarId;
   PCAR pCarInfront = pModell->asCars + iCarInfrontId;

   int iDiff = pCarInfront->iPosition - pMyCar->iPosition;
   iDiff += ((iDiff > 0) ? (-1) : (STREET_LENGTH));

   if (pMyCar->bIsInJam == true)
   {
      if (pMyCar->iV + pMyCar->iVChange > 0 && pMyCar->iV + pMyCar->iVChange <= iDiff)
      {
         //FALL D
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
            //FALL B
            pMyCar->iJamGroupId = pCarInfront->iJamGroupId;
         }
         else
         {
            //FALL A
            pMyCar->iJamGroupId = pModell->sGaugings.iTotalTrafficJams;
            pModell->sGaugings.iTotalTrafficJams++;
         }
      }
      else if (iDiff <= 1)
      {
         if (fDo_TestJam_OnOne(pModell, iCarInfrontId) == true)
         {
            //FALL C
            pMyCar->bIsInJam = true;
            pMyCar->iJamGroupId = pCarInfront->iJamGroupId;
         }
      }
   }

   return pMyCar->bIsInJam;
}

