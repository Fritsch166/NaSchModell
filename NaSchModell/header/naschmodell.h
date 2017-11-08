#ifndef _INC_NASCHMODELLH
#define _INC_NASCHMODELLH


#pragma warning( disable : 4710 464 )

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include <Utilities.h>
#include <object_car.h>
#include <drawbmp.h>
#include <colormap.h>

#define OP_DEFAULT '.'
#define OP_EXIT 'e'
#define OP_START 'q'
#define OP_CHANGEMODESTATE 'm'
#define OP_OPENMENUSAVE 'f'

#define FILLCHAR '#'


#define WINDOWWIDTH 108
#define MENUHEIGHT 4
#define STATUSHEIGHT 4
#define BOARDHEIGHT 8

struct naschmodell {

   int iTest;

};

typedef struct naschmodell * PMODELL;

#endif /* _INC_NASCHMODELLH */
