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

typedef const union hexToRGB * const COLOR;
typedef struct colormap * COLORMAP;

extern const union hexToRGB VALUE_RED;
extern const union hexToRGB VALUE_GREEN;
extern const union hexToRGB VALUE_BLUE;

#define RED   (&VALUE_RED)
#define GREEN (&VALUE_GREEN)
#define BLUE  (&VALUE_BLUE)

void initColorMap(COLORMAP map, const int iWidth, const int iHeight);
void setColorMap(COLORMAP map, COLOR color, int y, int x);
void freeColorMap(COLORMAP map);
