#ifndef _INC_COLORMAPH
#define _INC_COLORMAPH

struct colormap
{
   int iWidth;
   int iHeight;
   char ** ppRED;
   char ** ppGREEN;
   char ** ppBLUE;
};

typedef struct colormap CMAP;

#endif // _INC_COLORMAPH