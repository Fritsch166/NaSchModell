#pragma once

#pragma warning( disable : 4710 464 820 )

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "Utilities.h"

#define STREET_LENGTH 1000
#define PART_STREET_LENGTH 200
#define ARRAY_LENGTH 990

#define MAXTICKS 500

#define OP_DEFAULT '.'
#define OP_EXIT 'e'
#define OP_START 'q'
#define OP_CHANGEMODESTATE 'm'
#define OP_OPENMENUSAVE 'f'
#define OP_CHANGECRUISECONTROLSTATE 'c'
#define OP_CHANGEDELAYATV0STATE 'd'
#define OP_STOP 's'
#define OP_ENTER 13
#define OP_DEKREMENT '-'
#define OP_INKREMENT '+'
#define OP_SAVESETTINGS 5555555
#define OP_PRINT 'p'


#define FILLCHAR '#'
#define STREETCHAR '-'


#define WINDOWWIDTH 205
#define MENUHEIGHT 4
#define STATUSHEIGHT 4
#define BOARDHEIGHT 27
#define STATUS_SETTINGS_WIDTH 43
#define STATUS_GAUGINGS_WIDTH 31
#define SETTING_WINDOW_WIDTH 26
#define SETTING_WINDOW_HEIGHT 9



#define MAXWRITEPATHLENGTH 250
#define COMPLPATHLENGTH (MAXWRITEPATHLENGTH + 5)
#define TIMESTAMPLENGTH 50


enum states
{
   newtick = 0,
   accelerate,
   retard,
   dilly_dally,
   drive,
   test_jam
};

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
   enum toggle eTSaveToFile;
   enum mode eMode;
   char acFilename[COMPLPATHLENGTH];
   char acComplFilePath[COMPLPATHLENGTH];
};

struct gaugings
{
   int iTicks;
   int iTrafficJams;
   clock_t runtime;
   char acTimeStamp[TIMESTAMPLENGTH];

   //TODO colormap
};

struct object_car
{
   int iV;
   int iVChange;
   int iJamGroupId;
   int iPosition;
   bool bIsInJam;
   bool bDoDelayAtV0;
};

struct naschmodell
{
   struct settings sSettings;
   struct gaugings sGaugings;
   struct object_car asCars[ARRAY_LENGTH];
};


typedef struct naschmodell * PMODELL;
typedef struct object_car* ACAR;


void printFrame(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);
void deleteArea(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);
void printBoard(PMODELL pModell, enum states * pEState);
void printStatusSettings(PMODELL pModell);
void printStatusGaugings(PMODELL pModell);
int settingWindow(PMODELL pModell);


