#include "..\h-files\naschmodell.h"

static bool bIsInit = false;

struct colorschemes GLOBAL_ARRAY_COLOR_SCHEMES[MAX_COLOR_SCHEMES];

COLOR f1_Converter(struct saveState* pState);
COLOR f2_Converter(struct saveState* pState);
COLOR f3_Converter(struct saveState* pState);

void initGlobalColorSchemes(void)
{
   if (bIsInit == true)
   {
      return;
   }

   bIsInit = true;

   {
      struct colorschemes sF1 = {1, f1_Converter};
      struct colorschemes sF2 = {2, f2_Converter};
      struct colorschemes sF3 = {3, f3_Converter};

      GLOBAL_ARRAY_COLOR_SCHEMES[1] = sF1;
      GLOBAL_ARRAY_COLOR_SCHEMES[2] = sF2;
      GLOBAL_ARRAY_COLOR_SCHEMES[3] = sF3;
   }
}

COLOR f1_Converter(struct saveState* pState)
{
   //TODO
   return NULL;
}

COLOR f2_Converter(struct saveState* pState)
{
   //TODO
   return NULL;
}

COLOR f3_Converter(struct saveState* pState)
{
   //TODO
   return NULL;
}