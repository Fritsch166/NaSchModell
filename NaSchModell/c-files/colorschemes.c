#include "..\h-files\naschmodell.h"

static bool bIsInit = false;
struct colorschemes GLOBAL_ARRAY_COLOR_SCHEMES[9];

void initGlobalColorSchemes(void)
{
   if (bIsInit == false)
   {
      bIsInit = true;

      //TODO init color schemes
   }
}