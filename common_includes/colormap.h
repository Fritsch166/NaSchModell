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

extern const union uCOLOR VALUE_Aqua;
extern const union uCOLOR VALUE_Azure;
extern const union uCOLOR VALUE_Beige;
extern const union uCOLOR VALUE_Black;
extern const union uCOLOR VALUE_Blue;
extern const union uCOLOR VALUE_Brown;
extern const union uCOLOR VALUE_Chocolate;
extern const union uCOLOR VALUE_Coral;
extern const union uCOLOR VALUE_Crimson;
extern const union uCOLOR VALUE_Cyan;
extern const union uCOLOR VALUE_Fuchsia;
extern const union uCOLOR VALUE_Gold;
extern const union uCOLOR VALUE_Grey;
extern const union uCOLOR VALUE_Green;
extern const union uCOLOR VALUE_Indigo;
extern const union uCOLOR VALUE_Ivory;
extern const union uCOLOR VALUE_Khaki;
extern const union uCOLOR VALUE_Lavender;
extern const union uCOLOR VALUE_Lime;
extern const union uCOLOR VALUE_Linen;
extern const union uCOLOR VALUE_Magenta;
extern const union uCOLOR VALUE_Maroon;
extern const union uCOLOR VALUE_Navy;
extern const union uCOLOR VALUE_Olive;
extern const union uCOLOR VALUE_Orange;
extern const union uCOLOR VALUE_Orchid;
extern const union uCOLOR VALUE_Pink;
extern const union uCOLOR VALUE_Red;
extern const union uCOLOR VALUE_Silver;
extern const union uCOLOR VALUE_Snow;
extern const union uCOLOR VALUE_Tan;
extern const union uCOLOR VALUE_Tomato;
extern const union uCOLOR VALUE_Turquoise;
extern const union uCOLOR VALUE_Violet;
extern const union uCOLOR VALUE_White;
extern const union uCOLOR VALUE_Yellow;



#define Aqua  (&VALUE_Aqua )
#define Azure (&VALUE_Azure)
#define Beige (&VALUE_Beige)
#define Black  (&VALUE_Black )
#define Blue  (&VALUE_Blue )
#define Brown  (&VALUE_Brown )
#define Chocolate  (&VALUE_Chocolate )
#define Coral  (&VALUE_Coral )
#define Crimson  (&VALUE_Crimson )
#define Cyan  (&VALUE_Cyan )
#define Fuchsia  (&VALUE_Fuchsia )
#define Gold  (&VALUE_Gold )
#define Grey  (&VALUE_Grey )
#define Green  (&VALUE_Green )
#define Indigo   (&VALUE_Indigo  )
#define Ivory  (&VALUE_Ivory )
#define Khaki  (&VALUE_Khaki )
#define Lavender  (&VALUE_Lavender )
#define Lime  (&VALUE_Lime )
#define Linen  (&VALUE_Linen )
#define Magenta  (&VALUE_Magenta )
#define Maroon  (&VALUE_Maroon )
#define Navy  (&VALUE_Navy )
#define Olive  (&VALUE_Olive )
#define Orange  (&VALUE_Orange )
#define Orchid  (&VALUE_Orchid )
#define Pink  (&VALUE_Pink )
#define Red  (&VALUE_Red )
#define Silver  (&VALUE_Silver )
#define Snow  (&VALUE_Snow )
#define Tan  (&VALUE_Tan )
#define Tomato  (&VALUE_Tomato )
#define Turquoise  (&VALUE_Turquoise )
#define Violet  (&VALUE_Violet )
#define White  (&VALUE_White )
#define Yellow  (&VALUE_Yellow )



void initColorMap(COLORMAP map, const int iWidth, const int iHeight);
void setColorMap(COLORMAP map, COLOR color, const int y, const int x);
void freeColorMap(COLORMAP map);
COLOR getMixedColor(COLOR pColor0, COLOR pColorN, const int iN, const int iI);
