

#include "..\h-files\colormap.h"

const union hexToRGB VALUE_RED = {.uiHEX = 0xff0000};
const union hexToRGB VALUE_GREEN = {.uiHEX = 0x00ff00};
const union hexToRGB VALUE_BLUE = {.uiHEX = 0x0000ff};



/*
#define initColorMap(map,iWidth,iHeight)              \
map->iWidth = iWidth;                                 \
map->iHeight = iHeight;                               \
map->ppucRED   = malloc(sizeof(char**)*iWidth);       \
map->ppucGREEN = malloc(sizeof(char**)*iWidth);       \
map->ppucBLUE  = malloc(sizeof(char**)*iWidth);       \
for ( int i = 0 ; i < iWidth ; i++ ) {                \
map->ppucRED[i]   = calloc(iHeight, sizeof(char*));\
map->ppucGREEN[i] = calloc(iHeight, sizeof(char*));\
map->ppucBLUE[i]  = calloc(iHeight, sizeof(char*));\
}


#define setColorMap(map,color,y,x)         \
map->ppucRED[x][y]   = (color)->sRGB.ucRED;  \
map->ppucGREEN[x][y] = (color)->sRGB.ucGREEN;\
map->ppucBLUE[x][y]  = (color)->sRGB.ucBLUE;

*/
