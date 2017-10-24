#ifndef DSP_H
#define DSP_H

#include "wav.h"

int sizeConvolution(int size_f, int size_g);
// double * convolucion(double * f, double * g, int size_f, int size_g);

ArrayDouble muestrear(ArrayDouble arr, int frecuenciaMuestreoMhz, WAVHeader wh);

//Transformada Discreta de Fourier
ArrayComplex transformadaFourier(ArrayDouble x);
ArrayComplex transformadaFourierInversa(ArrayComplex x);

//Funciones a aplicar sobre las muestras
short * mediaAmplitud(short *samples, unsigned long cantidad);
short * convolucionShort(short * muestras, double * f, int cantMuestras, int size_f);
ArrayDouble convolucion(ArrayDouble f, ArrayDouble g);
ArrayDouble mapSamplesConvoluted(ArrayDouble muestras, ArrayDouble conv);
ArrayDouble mapFromOne(ArrayDouble muestras);
ArrayDouble mapToOne(ArrayDouble muestras);

ArrayShort multiplicarMuestras(ArrayShort a, ArrayShort b);
ArrayDouble mapSamplesConvoluted(ArrayDouble muestras, ArrayDouble conv);

ArrayDouble generarSeno(int items, int fm);
ArrayDouble generarCoseno(int items, int fm);


#endif
