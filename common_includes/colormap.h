#pragma once


struct colormap
{
   int iWidth;
   int iHeight;
   unsigned char ** ppucRED;
   unsigned char ** ppucGREEN;
   unsigned char ** ppucBLUE;
};

union uCOLOR
{
   unsigned int uiHEX;
   struct
   {
      unsigned char ucBLUE;
      unsigned char ucGREEN;
      unsigned char ucRED;
   } sRGB;
};

typedef const union uCOLOR * const COLOR;
typedef struct colormap * COLORMAP;

extern const union uCOLOR VALUE_RED;
extern const union uCOLOR VALUE_GREEN;
extern const union uCOLOR VALUE_BLUE;

#define RED   (&VALUE_RED)
#define GREEN (&VALUE_GREEN)
#define BLUE  (&VALUE_BLUE)

void initColorMap(COLORMAP map, const int iWidth, const int iHeight);
void setColorMap(COLORMAP map, COLOR color, int y, int x);
void freeColorMap(COLORMAP map);
