#include "object_car.h"

#include <stdlib.h>


struct object_data_car {

   unsigned char ucId;
   unsigned char ucSpeed;
   char cAcceleration;

};

typedef struct object_data_car * odcar;



OCAR newCar(void)
{
   static unsigned char ucCOUNTER = 0;
   odcar psdcar = 0;


   psdcar = malloc(sizeof(struct object_data_car) * 1);

   if (psdcar == 0) {
      return (OCAR)(0);
   }

   psdcar->ucId = ucCOUNTER;
   psdcar->ucSpeed = 0;
   psdcar->cAcceleration = 0;

   ucCOUNTER += 1;

   return (OCAR)psdcar;
}


void freeCar(OCAR psCar)
{
   odcar psdcar = (odcar)(psCar);

   free(psdcar);
}

