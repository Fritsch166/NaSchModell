
#include "..\h-files\colormap.h"

#include <stdlib.h>

const union uCOLOR VALUE_Aqua = {.uiHEX = 0x00FFFF};
const union uCOLOR VALUE_Azure = {.uiHEX = 0xF0FFFF};
const union uCOLOR VALUE_Beige = {.uiHEX = 0xF5F5DC};
const union uCOLOR VALUE_Black = {.uiHEX = 0x000000};
const union uCOLOR VALUE_Blue = {.uiHEX = 0x0000FF};
const union uCOLOR VALUE_Brown = {.uiHEX = 0xA52A2A};
const union uCOLOR VALUE_Chocolate = {.uiHEX = 0xD2691E};
const union uCOLOR VALUE_Coral = {.uiHEX = 0xFF7F50};
const union uCOLOR VALUE_Crimson = {.uiHEX = 0xDC143C};
const union uCOLOR VALUE_Cyan = {.uiHEX = 0x00FFFF};
const union uCOLOR VALUE_Fuchsia = {.uiHEX = 0xFF00FF};
const union uCOLOR VALUE_Gold = {.uiHEX = 0xFFD700};
const union uCOLOR VALUE_Grey = {.uiHEX = 0x808080};
const union uCOLOR VALUE_Green = {.uiHEX = 0x008000};
const union uCOLOR VALUE_Indigo = {.uiHEX = 0x4B0082};
const union uCOLOR VALUE_Ivory = {.uiHEX = 0xFFFFF0};
const union uCOLOR VALUE_Khaki = {.uiHEX = 0xF0E68C};
const union uCOLOR VALUE_Lavender = {.uiHEX = 0xE6E6FA};
const union uCOLOR VALUE_Lime = {.uiHEX = 0x00FF00};
const union uCOLOR VALUE_Linen = {.uiHEX = 0xFAF0E6};
const union uCOLOR VALUE_Magenta = {.uiHEX = 0xFF00FF};
const union uCOLOR VALUE_Maroon = {.uiHEX = 0x800000};
const union uCOLOR VALUE_Navy = {.uiHEX = 0x000080};
const union uCOLOR VALUE_Olive = {.uiHEX = 0x808000};
const union uCOLOR VALUE_Orange = {.uiHEX = 0xFFA500};
const union uCOLOR VALUE_Orchid = {.uiHEX = 0xDA70D6};
const union uCOLOR VALUE_Pink = {.uiHEX = 0xFFC0CB};
const union uCOLOR VALUE_Red = {.uiHEX = 0xFF0000};
const union uCOLOR VALUE_Silver = {.uiHEX = 0xC0C0C0};
const union uCOLOR VALUE_Snow = {.uiHEX = 0xFFFAFA};
const union uCOLOR VALUE_Tan = {.uiHEX = 0xD2B48C};
const union uCOLOR VALUE_Tomato = {.uiHEX = 0xFF6347};
const union uCOLOR VALUE_Turquoise = {.uiHEX = 0x40E0D0};
const union uCOLOR VALUE_Violet = {.uiHEX = 0xEE82EE};
const union uCOLOR VALUE_White = {.uiHEX = 0xFFFFFF};
const union uCOLOR VALUE_Yellow = {.uiHEX = 0xFFFF00};


void initColorMap(COLORMAP map, const int iWidth, const int iHeight)
{
   map->iWidth = iWidth;
   map->iHeight = iHeight;

   map->ppucRED = malloc(sizeof(char*)*iWidth);
   map->ppucGREEN = malloc(sizeof(char*)*iWidth);
   map->ppucBLUE = malloc(sizeof(char*)*iWidth);

   for (int i = 0; i < iWidth; i++)
   {
      map->ppucRED[i] = calloc(iHeight, sizeof(char));
      map->ppucGREEN[i] = calloc(iHeight, sizeof(char));
      map->ppucBLUE[i] = calloc(iHeight, sizeof(char));
   }
}

void freeColorMap(COLORMAP map)
{
   for (int i = 0; i < map->iWidth; i++)
   {
      free(map->ppucRED[i]);
      free(map->ppucGREEN[i]);
      free(map->ppucBLUE[i]);

      map->ppucRED[i] = NULL;
      map->ppucGREEN[i] = NULL;
      map->ppucBLUE[i] = NULL;
   }

   free(map->ppucBLUE);
   free(map->ppucGREEN);
   free(map->ppucRED);

   map->ppucBLUE = NULL;
   map->ppucGREEN = NULL;
   map->ppucRED = NULL;

   map = NULL;
}


void setColorMap(COLORMAP map, COLOR color, const int y, const int x)
{
   if (x >= 0 && x < map->iWidth)
   {
      if (y >= 0 && y < map->iHeight)
      {
         map->ppucRED[x][y] = (color)->sRGB.ucRED;
         map->ppucGREEN[x][y] = (color)->sRGB.ucGREEN;
         map->ppucBLUE[x][y] = (color)->sRGB.ucBLUE;
      }
   }
}

