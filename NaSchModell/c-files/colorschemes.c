#include "..\h-files\naschmodell.h"

#define NUMBER_OF_COLORS 32

static bool bIsInit = false;
static COLOR pCOLOR_LIST[NUMBER_OF_COLORS] = {
Aqua ,
Azure,
Beige,
Blue ,
Brown ,
Chocolate ,
Coral ,
Crimson ,
Cyan ,
Fuchsia ,
Gold ,
Grey ,
Indigo  ,
Ivory ,
Khaki ,
Lavender ,
Lime ,
Linen ,
Magenta ,
Maroon ,
Navy ,
Olive ,
Orange ,
Orchid ,
Pink ,
Silver ,
Snow ,
Tan ,
Tomato ,
Turquoise ,
Violet ,
Yellow
};

struct colorschemes GLOBAL_ARRAY_COLOR_SCHEMES[MAX_COLOR_SCHEMES];

COLOR f1_Converter(struct saveState* pState, struct settings * pSettings);
COLOR f2_Converter(struct saveState* pState, struct settings * pSettings);
COLOR f3_Converter(struct saveState* pState, struct settings * pSettings);




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

COLOR f1_Converter(struct saveState* pState, struct settings * pSettings)
{
   if (pState == NULL)
   {
      return Black;
   }
   if (pState->bIsInJam == true)
   {
      return Red;
   }
   if (pState->bIsInJam == false)
   {
      return White;
   }

   return NULL;
}

COLOR f2_Converter(struct saveState* pState, struct settings * pSettings)
{
   if (pState == NULL)
   {
      return Black;
   }
   if (pState->bIsInJam == true)
   {
      return Red;
   }
   if (pState->bIsInJam == false)
   {
      return getMixedColor(Red, Green, pSettings->iVMax, pState->iVTotal);
   }
   return NULL;
}

COLOR f3_Converter(struct saveState* pState, struct settings * pSettings)
{
   if (pState == NULL)
   {
      return Black;
   }
   if (pState->bIsInJam == true)
   {
      return pCOLOR_LIST[pState->iJamGroup % NUMBER_OF_COLORS];
   }
   if (pState->bIsInJam == false)
   {
      return White;
   }
   return NULL;
}



