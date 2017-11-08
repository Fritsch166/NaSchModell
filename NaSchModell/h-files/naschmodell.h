#pragma once

#pragma warning( disable : 4710 464 820 )

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "Utilities.h"
#include "object_car.h"

#define ARRAY_LENGTH 990

#define OP_DEFAULT '.'
#define OP_EXIT 'e'
#define OP_START 'q'
#define OP_CHANGEMODESTATE 'm'
#define OP_OPENMENUSAVE 'f'
#define OP_CHANGECRUISECONTROLSTATE 'c'
#define OP_CHANGEDELAYATV0STATE 'd'

#define FILLCHAR '#'
#define STREETCHAR '-'


#define WINDOWWIDTH 205
#define MENUHEIGHT 4
#define STATUSHEIGHT 4
#define BOARDHEIGHT 27
#define STATUS_SETTINGS_WIDTH 43

#define STREET_LENGTH 1000
#define PART_STREET_LENGTH 200


#define MAXWRITEPATHLENGTH 250
#define COMPLPATHLENGTH (MAXWRITEPATHLENGTH + 5)
#define TIMESTAMPLENGTH 50


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

   //! Storage of the written filename
   char acFilename[COMPLPATHLENGTH];

   //! Storage of the complete filename [acFilename + ".bmp\0"]
   char acComplFilePath[COMPLPATHLENGTH];
};

struct gaugings
{
   int iTicks;
   int iTrafficJams;

   //! Time storage when the algorithm is started. Saves the time since the program runs.
   clock_t runtime;

   //! Storage of the time stamp. Time without jam
   char acTimeStamp[TIMESTAMPLENGTH];
   
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
void printBoard(PMODELL pModell, int iView);
void printStatusSettings(PMODELL pModell);
void printStatusGaugings(PMODELL pModell);


