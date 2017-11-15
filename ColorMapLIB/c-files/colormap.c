
#include "..\h-files\colormap.h"

#include <stdlib.h>

const union uCOLOR VALUE_RED = {.uiHEX = 0xff0000};
const union uCOLOR VALUE_GREEN = {.uiHEX = 0x00ff00};
const union uCOLOR VALUE_BLUE = {.uiHEX = 0x0000ff};


void initColorMap(COLORMAP map, const int iWidth, const int iHeight)
{
   map->iWidth = iWidth;
   map->iHeight = iHeight;

   map->ppucRED = malloc(sizeof(char**)*iWidth);
   map->ppucGREEN = malloc(sizeof(char**)*iWidth);
   map->ppucBLUE = malloc(sizeof(char**)*iWidth);

   for (int i = 0; i < iWidth; i++)
   {
      map->ppucRED[i] = calloc(iHeight, sizeof(char*));
      map->ppucGREEN[i] = calloc(iHeight, sizeof(char*));
      map->ppucBLUE[i] = calloc(iHeight, sizeof(char*));
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

