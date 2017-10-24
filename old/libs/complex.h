#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct ComplexNumber{
  double real;
  double imag;
} ComplexNumber;

ComplexNumber newComplexNumber(double real, double imag);
double getMagnitud(ComplexNumber c);
double getAngulo(ComplexNumber c);

#endif
