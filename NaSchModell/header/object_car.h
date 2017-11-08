
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
   bool bEnable;
};

typedef struct object_car* ACAR;

#include <naschmodell.h>

void disableAllCars(ACAR asCars);
void enableCars(ACAR asCars, const int iCars);

#endif /* _INC_OBJECT_CAR_H */

