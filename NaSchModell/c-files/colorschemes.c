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
COLOR getMixedColor(COLOR pColor0, COLOR pColorN, const int iN, const int iI);



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



COLOR getMixedColor(COLOR pColor0, COLOR pColorN, const int iN, const int iI)
{
   static union uCOLOR uColor;

   unsigned int uiColorN_RGB = pColorN->uiHEX;

   unsigned char ucColorN_R = (unsigned char)((uiColorN_RGB & 0x00FF0000) >> 16);
   unsigned char ucColorN_G = (unsigned char)((uiColorN_RGB & 0x0000FF00) >> 8);
   unsigned char ucColorN_B = (unsigned char)((uiColorN_RGB & 0x000000FF) >> 0);

   unsigned int uiColor0_RGB = pColor0->uiHEX;

   unsigned char ucColor0_R = (unsigned char)((uiColor0_RGB & 0x00FF0000) >> 16);
   unsigned char ucColor0_G = (unsigned char)((uiColor0_RGB & 0x0000FF00) >> 8);
   unsigned char ucColor0_B = (unsigned char)((uiColor0_RGB & 0x000000FF) >> 0);

   int iDiff_R = ucColorN_R - ucColor0_R;
   int iDiff_G = ucColorN_G - ucColor0_G;
   int iDiff_B = ucColorN_B - ucColor0_B;

   double dStepValue_R = iDiff_R / (double)(iN);
   double dStepValue_G = iDiff_G / (double)(iN);
   double dStepValue_B = iDiff_B / (double)(iN);


   unsigned char ucColorI_R = (unsigned char)(ucColor0_R + dStepValue_R * iI);
   unsigned char ucColorI_G = (unsigned char)(ucColor0_G + dStepValue_G * iI);
   unsigned char ucColorI_B = (unsigned char)(ucColor0_B + dStepValue_B * iI);

   unsigned int uiColorI_R = ucColorI_R;
   unsigned int uiColorI_G = ucColorI_G;
   unsigned int uiColorI_B = ucColorI_B;

   unsigned int uiColorI_RGB = (uiColorI_R << 16) | (uiColorI_G << 8) | (uiColorI_B << 0);

   uColor.uiHEX = uiColorI_RGB;

   return &uColor;
}