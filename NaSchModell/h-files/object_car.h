
#pragma once

#include <stdbool.h>

struct object_car
{
   int iV;
   int iVChange;
   int iJamGroupId;
   int iPosition;
   bool bIsInJam;
};

typedef struct object_car* ACAR;

#include "naschmodell.h"

void initCars(ACAR asCars, const int iCars);

