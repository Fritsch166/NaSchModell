#pragma once


struct object_car 
{
   const unsigned bit : 1;
};


typedef const struct object_car * OCAR;


OCAR newCar(void);
void freeCar(OCAR psCar);




