#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <Windows.h>

#include "Utilities.h"

#include "..\..\common_includes\drawbmp.h"
#include "..\..\common_includes\colormap.h"


#define STREET_LENGTH 1000
#define PART_STREET_LENGTH 200
#define ARRAY_CARS_MAX_LENGTH 990
#define MAX_COLOR_SCHEMES 10

#define MAXTICKS 500

#define OP_DEFAULT '.'
#define OP_EXIT 'e'
#define OP_START 'q'
#define OP_OPENMENUSAVE 'f'
#define OP_STOP 's'
#define OP_ENTER 13
#define OP_DEKREMENT '-'
#define OP_INKREMENT '+'
#define OP_SAVESETTINGS 5555555
#define OP_PRINT 'p'
#define OP_STEP ' '
#define OP_TAB 9
#define OP_REMOVE 8
#define OP_ESC 27
#define OP_BACKSPACE 8
#define OP_CHANGESAVESTATE '>'


#define FILLCHAR '#'
#define STREETCHAR '-'


#define WINDOWWIDTH 205
#define MENUHEIGHT 4
#define STATUSHEIGHT 5
#define BOARDHEIGHT 27
#define STATUS_SETTINGS_WIDTH 45
#define STATUS_GAUGINGS_WIDTH 34
#define SETTING_WINDOW_WIDTH 32
#define SETTING_WINDOW_HEIGHT 15
#define PRINT_WINDOW_WIDTH 33
#define PRINT_WINDOW_HEIGHT 11



#define MAXWRITEPATHLENGTH 180
#define COMPLPATHLENGTH (MAXWRITEPATHLENGTH + 6)
#define TIMESTAMPLENGTH 12

extern struct colorschemes GLOBAL_ARRAY_COLOR_SCHEMES[MAX_COLOR_SCHEMES];

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
   off = 0,
   on
};

enum mode
{
   step1 = 0,
   step6,
   auto6,
   autoX
};


struct settings
{
   int iVMax;
   int iCars;
   int iPDDProzent;
   enum toggle eTCruiseControl;
   int iIncreasedDelayAtV0Prozent;
   enum toggle eTSaveToFile;
   enum mode eMode;
   char acFilename[COMPLPATHLENGTH+1];
   char acComplFilePath[COMPLPATHLENGTH+1];
   struct colorschemes* apsCSchemes[MAX_COLOR_SCHEMES];
};

struct saveState
{
   bool bIsInJam;
   int iVTotal;
   int iJamGroup;
   int iPosition;
};

struct gaugings
{
   int iTicks;
   int iTotalTrafficJams;
   int iCurrentTrafficJams;
   clock_t runtime;
   char acTimeStamp[TIMESTAMPLENGTH];
   struct saveState ** ppsState;
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
   struct object_car asCars[ARRAY_CARS_MAX_LENGTH];
};

struct colorschemes
{
   unsigned int iId;
   COLOR(*pf_Converter)(struct saveState*, struct settings*);
};


typedef struct naschmodell * PMODELL;
typedef struct object_car* PCAR;

extern const char * const GLOBAL_APC_MODETEXT[4];

void printFrame(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);
void deleteArea(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight);
void printMainMenue(void);
void printBoard(PMODELL pModell, const enum states * pEState);
void printStatusSettings(PMODELL pModell);
void printStatusGaugings(PMODELL pModell);
int settingWindow(PMODELL pModell);
int calcNaSchModell(PMODELL pModell);
void initGlobalColorSchemes(void);
void printToFile(PMODELL pModell);
int input(const short int siX, const short int siY);
void printWindow(PMODELL pModell);

