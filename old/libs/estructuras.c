#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "estructuras.h"

#define mayor(a,b) (a > b ? a : b)


ArrayDouble newArrayDouble(int size){
  ArrayDouble arrayDouble;
  arrayDouble.items = (double *) malloc(sizeof(double) * size);
  arrayDouble.length = size;
  return arrayDouble;
}

ArrayShort  newArrayShort(int size){
  ArrayShort arrayShort;
  arrayShort.items = (short *) malloc(sizeof(short) * size);
  arrayShort.length = size;
  return arrayShort;
}

ArrayComplex  newArrayComplex(int size){
  ArrayComplex arrayComplex;
  arrayComplex.items = (ComplexNumber *) malloc(sizeof(ComplexNumber) * size);
  arrayComplex.length = size;
  return arrayComplex;
}


void printArrayDouble(ArrayDouble a){
  printf(" ---- %d Elementos: -----\n", a.length);
  for (int i = 0; i < a.length; i++) {
    printf("\t[%d] %f\n", i, a.items[i]);
  }
  printf("\n");
}

void printArrayShort(ArrayShort a){
  printf(" ---- %d Elementos: -----\n", a.length);
  for (int i = 0; i < a.length; i++) {
    printf("\t[%d] %d\n", i, a.items[i]);
  }
  printf("\n");
}

void printArrayComplex(ArrayComplex a){
  printf(" ---- %d Elementos: -----\n", a.length);
  for (int i = 0; i < a.length; i++) {
    printf("\t[%d] %f + %fj\n", i, a.items[i].real, a.items[i].imag);
  }
  printf("\n");
}

ArrayDouble mapArrayDouble(ArrayDouble a, double from, double to){
  double input_start, input_end;
  ArrayDouble mapeado = newArrayDouble(a.length);
  input_start = a.items[0];
  input_end = a.items[0];
  for (int i = 0; i < a.length; i++) {
    if(a.items[i] < input_start) input_start = a.items[i];
    if(a.items[i] > input_end) input_end = a.items[i];
  }

  // printf("[%f, %f] => [%f, %f]\n", input_start, input_end, from, to);
  for (int i = 0; i < mapeado.length; i++) {
    mapeado.items[i] = (a.items[i] - input_start) / (input_end - input_start) * (to - from) + from;
  }

  return mapeado;
}


ArrayShort mapArrayShort(ArrayShort a, short from, short to){
  short input_start, input_end;
  ArrayShort mapeado = newArrayShort(a.length);
  input_start = a.items[0];
  input_end = a.items[0];
  for (int i = 0; i < a.length; i++) {
    if(a.items[i] < input_start) input_start = a.items[i];
    if(a.items[i] > input_end) input_end = a.items[i];
  }

  for (int i = 0; i < mapeado.length; i++) {
    mapeado.items[i] = (a.items[i] - input_start) / (input_end - input_start) * (to - from) + from;
  }

  return mapeado;
}

ArrayDouble arrayShortToArrayDouble(ArrayShort a){
    ArrayDouble b = newArrayDouble(a.length);
    for (int i = 0; i < a.length; i++) {
      b.items[i] = (double) a.items[i];
    }
    return b;
}

ArrayShort arrayDoubleToArrayShort(ArrayDouble a){
  ArrayShort b = newArrayShort(a.length);
  for (int i = 0; i < a.length; i++) {
    b.items[i] = (short) a.items[i];
  }
  return b;
}

short getMayorShort(ArrayShort a){
  short m = 0;
  for (int i = 0; i < a.length; i++) {
    if( a.items[i] > m) m =  a.items[i];
  }
  return m;
}

short getMenorShort(ArrayShort a){
  short m = 0;
  for (int i = 0; i < a.length; i++) {
    if( a.items[i] < m) m =  a.items[i];
  }
  return m;
}

double getMayorDouble(ArrayDouble a){
  double m = 0;
  for (int i = 0; i < a.length; i++) {
    if( a.items[i] > m) m =  a.items[i];
  }
  return m;
}

double getMenorDouble(ArrayDouble a){
  double m = 0;
  for (int i = 0; i < a.length; i++) {
    if( a.items[i] < m) m =  a.items[i];
  }
  return m;
}

ArrayDouble multiplyArraysDouble(ArrayDouble a, ArrayDouble b){
  int len = mayor(a.length, b.length);
  ArrayDouble c = newArrayDouble(len);

  for (int i = 0; i < len; i++) {
    c.items[i] = -1;
    if(a.length-1 >= i && b.length-1 >= i){
      c.items[i] = a.items[i] * b.items[i];
    }else if(a.length-1 >= i){
      c.items[i] = a.items[i];
    }else{
      c.items[i] = b.items[i];
    }
  }
  return c;
}



ArrayDouble applyEach(ArrayDouble a, double (*fn)(double val, int idx, ArrayDouble * arr) ){
  ArrayDouble b = newArrayDouble(a.length);
  for (int i = 0; i < a.length; i++) {
    b.items[i] = fn(a.items[i], i, &a);
  }
  return b;
}

double porDos(double val, int idx, ArrayDouble * arr){
  return val * 2;
}

double llenarConSeno(double val, int idx, ArrayDouble * arr){
  return sin(idx);
}


ArrayDouble getRealFromComplex(ArrayComplex c){
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    out.items[i] = c.items[i].real > 1 ?  1 : c.items[i].real < -1 ? -1 : c.items[i].real;
  }
  return out;
}

ArrayDouble getImagFromComplex(ArrayComplex c){
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    out.items[i] = c.items[i].imag;
  }
  return out;
}

ArrayDouble getArrayMagComplex(ArrayComplex c){
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    double m =  getMagnitud(c.items[i]);
    out.items[i] = m > 1 ? 1 : m < -1 ? -1 : m;
  }
  return out;
}

ArrayDouble getArrayAngComplex(ArrayComplex c){
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    double m =  getAngulo(c.items[i]);
    out.items[i] = m;
    // out.items[i] = m > 1 ? 1 : m < -1 ? -1 : m;
  }
  return out;
}
