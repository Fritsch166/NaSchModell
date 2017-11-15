#pragma once


struct colormap
{
   int iWidth;
   int iHeight;
   unsigned char ** ppucRED;
   unsigned char ** ppucGREEN;
   unsigned char ** ppucBLUE;
};

struct cMapColor
{
   unsigned char ucBLUE;
   unsigned char ucGREEN;
   unsigned char ucRED;
};

union hexToRGB
{
   unsigned int uiHEX;
   struct cMapColor sRGB;
};

typedef union hexToRGB* COLOR;

extern const union hexToRGB VALUE_RED;
extern const union hexToRGB VALUE_GREEN;
extern const union hexToRGB VALUE_BLUE;

#define RED   (&VALUE_RED)
#define GREEN (&VALUE_GREEN)
#define BLUE  (&VALUE_BLUE)

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

