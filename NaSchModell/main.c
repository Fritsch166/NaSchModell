
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "object_car.h"

#pragma warning( disable : 4710 )

int main(void)
{

   OCAR psCar1 = 0;
   int iReturn = 0;

   printf("\033[31mDieser Text ist rot!\n");
   printf("\033[1mDieser Text ist fett!\n");
   printf("\033[mDieser Text ist wieder normal!\n");


   psCar1 = newCar();


   //TODO

   iReturn = _getch();
   if (iReturn > 0) {
      iReturn = EXIT_SUCCESS;
   }


   freeCar(psCar1);


   return iReturn;
}
