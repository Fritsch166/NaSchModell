#include "..\h-files\naschmodell.h"

void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions);

void initModell(PMODELL pModell)
{

   //! default settings
   pModell->sSettings.eMode = step1;
   pModell->sSettings.eTSaveToFile = off;
   pModell->sSettings.eTCruiseControl = off;
   pModell->sSettings.iIncreasedDelayAtV0Prozent = 0;
   pModell->sSettings.iCars = 1;
   pModell->sSettings.iPDDProzent = 33;
   pModell->sSettings.iVMax = 5;
   for (int i = 0; i < COMPLPATHLENGTH; i++)
   {
      pModell->sSettings.acFilename[i] = 0;
      pModell->sSettings.acComplFilePath[i] = 0;
      (i < TIMESTAMPLENGTH) ? (pModell->sGaugings.acTimeStamp[i] = 0) : (0);
      (i < MAX_COLOR_SCHEMES) ? (pModell->sSettings.apsCSchemes[i] = NULL) : (0);
   }

   //! default gaugings
   pModell->sGaugings.ppsState = (struct saveState **) malloc(sizeof(struct saveState *) * ARRAY_CARS_MAX_LENGTH);
   for (unsigned int iX = 0; iX < ARRAY_CARS_MAX_LENGTH; iX++)
   {
      pModell->sGaugings.ppsState[iX] = (struct saveState *) malloc(sizeof(struct saveState) * MAXTICKS);
   }

   //! cars
   initCarsAndGaugings(pModell);
}

void initCarsAndGaugings(PMODELL pModell)
{
   //! init cars and gaugings
   pModell->sGaugings.iTicks = 0;
   pModell->sGaugings.iTotalTrafficJams = 0;
   pModell->sGaugings.iCurrentTrafficJams = 0;
   pModell->sGaugings.runtime = 0;

   {
      int aiPositions[STREET_LENGTH];
      randomize(aiPositions, pModell->sSettings.iCars);
      for (int i = 0; i < pModell->sSettings.iCars; i++)
      {

         pModell->asCars[i].bIsInJam = false;
         pModell->asCars[i].bDoDelayAtV0 = false;
         pModell->asCars[i].iJamGroupId = -1;
         pModell->asCars[i].iVChange = 0;
         pModell->asCars[i].iV = rand() % (pModell->sSettings.iVMax + 1);
         pModell->asCars[i].iPosition = aiPositions[i];

      }
   }
}


void randomize(int aiPositions[STREET_LENGTH], const int iAmountPositions)
{

   //init array
   for (int iPosition = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      aiPositions[iPosition] = -1;
   }

   //calc random positions
   for (int iN = 0; iN < iAmountPositions;)
   {
      int iPosition = (rand() % STREET_LENGTH);

      if (aiPositions[iPosition] < 0)
      {
         aiPositions[iPosition] = iPosition;
         iN++;
      }
   }

   //Sort psitions at array start
   for (int iPosition = 0, iN = 0; iPosition < STREET_LENGTH; iPosition++)
   {
      if (aiPositions[iPosition] >= 0)
      {
         aiPositions[iN++] = aiPositions[iPosition];
      }
   }
}

