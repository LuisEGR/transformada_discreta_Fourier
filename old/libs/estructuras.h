#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "complex.h"

typedef struct ArrayDouble{
  unsigned int length;
  double * items;
} ArrayDouble;

typedef struct ArrayShort{
  unsigned int length;
  short * items;
} ArrayShort;

typedef struct ArrayComplex{
  unsigned int length;
  ComplexNumber * items;
} ArrayComplex;

ArrayDouble newArrayDouble(int size);
ArrayShort  newArrayShort(int size);
ArrayComplex  newArrayComplex(int size);

void printArrayDouble(ArrayDouble a);
void printArrayShort(ArrayShort a);
void printArrayComplex(ArrayComplex a);

ArrayDouble mapArrayDouble(ArrayDouble a, double from, double to);
ArrayShort mapArrayShort(ArrayShort a, short from, short to);

ArrayDouble arrayShortToArrayDouble(ArrayShort a);
ArrayShort arrayDoubleToArrayShort(ArrayDouble a);

short getMayorShort(ArrayShort a);
short getMenorShort(ArrayShort a);

double getMayorDouble(ArrayDouble a);
double getMenorDouble(ArrayDouble a);

ArrayDouble multiplyArraysDouble(ArrayDouble a, ArrayDouble b);

ArrayDouble applyEach(ArrayDouble a, double (*fn)(double val, int idx, ArrayDouble * arr) );
//Functions to use with ApplyEach
double porDos(double val, int idx, ArrayDouble * arr);
double llenarConSeno(double val, int idx, ArrayDouble * arr);

ArrayDouble getRealFromComplex(ArrayComplex c);
ArrayDouble getImagFromComplex(ArrayComplex c);
ArrayDouble getArrayMagComplex(ArrayComplex c);
ArrayDouble getArrayAngComplex(ArrayComplex c);

#endif
