#ifndef _INC_NASCHMODELLH
#define _INC_NASCHMODELLH

#pragma warning( disable : 4710 464 820 )

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include <Utilities.h>
#include <object_car.h>
#include <drawbmp.h>
#include <colormap.h>

#define ARRAY_LENGTH 990

#define OP_DEFAULT '.'
#define OP_EXIT 'e'
#define OP_START 'q'
#define OP_CHANGEMODESTATE 'm'
#define OP_OPENMENUSAVE 'f'

#define FILLCHAR '#'


#define WINDOWWIDTH 206
#define MENUHEIGHT 4
#define STATUSHEIGHT 4
#define BOARDHEIGHT 30


enum toggle
{
   off,
   on
};

enum mode
{
   step,
   automatic
};


struct settings
{
   int iVMax;
   int iCars;
   int iPProzent;
   enum toggle eTCruiseControl;
   enum toggle eTDelayedAtV0;
   //TODO enum toggle eTSaveToFile;
   enum mode eMode;
   //TODO acFilepath
};

struct gaugings
{
   int iTicks;
   int iTrafficJams;
   //TODO time
   //TODO colormap
};

struct naschmodell
{
   struct settings sSettings;
   struct gaugings sGaugings;
   struct object_car asCars[ARRAY_LENGTH];
};


typedef struct naschmodell * PMODELL;


void printFrame(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);
void deleteArea(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);



#endif /* _INC_NASCHMODELLH */
