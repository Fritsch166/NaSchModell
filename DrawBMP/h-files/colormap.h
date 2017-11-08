#pragma once

struct colormap
{
   int iWidth;
   int iHeight;
   char ** ppRED;
   char ** ppGREEN;
   char ** ppBLUE;
};

typedef struct colormap CMAP;