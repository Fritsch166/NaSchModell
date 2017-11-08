
#include <object_car.h>
#include <stdlib.h>
#include <stdbool.h>


struct object_data_car
{

   int iId;
   int iV;
   int iVChange;
  

};

typedef struct object_data_car * odcar;



OCAR newCar(void)
{
   static int iCOUNTER = 0;
   odcar psdcar = 0;


   psdcar = malloc(sizeof(struct object_data_car) * 1);

   if (psdcar == 0) {
      return (OCAR)(0);
   }

   psdcar->iId = iCOUNTER;
   psdcar->iV = 0;
   psdcar->iVChange = 0;

   iCOUNTER += 1;

   return (OCAR)psdcar;
}


void freeCar(OCAR psCar)
{
   odcar psdcar = (odcar)(psCar);

   free(psdcar);
}

