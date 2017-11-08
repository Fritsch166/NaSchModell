
#ifndef _INC_OBJECT_CAR_H
#define _INC_OBJECT_CAR_H

#include <stdbool.h>

struct object_car
{
   int iV;
   int iVChange;
   int iJamGroupId;
   int iPosition;
   bool bIsInJam;
};

typedef struct object_car * PCAR;

#include <naschmodell.h>

void initCars(PCAR* apsCars);
PCAR* newCars(PCAR* apsCars, const int iCars);
void freeCars(PCAR* apsCars);

#endif /* _INC_OBJECT_CAR_H */

