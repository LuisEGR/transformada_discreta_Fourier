#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "estructuras.h"
#include "dsp.h"
#include "wav.h"

int sizeConvolution(int size_f, int size_g){
  return size_f + size_g - 1;
}

int mayor(int a, int b){
  return a > b ? a : b;
}

int menor(int a, int b){
  return a > b ? b : a;
}

ArrayDouble convolucion(ArrayDouble f, ArrayDouble g){
  int i, j, muestras_y, i1;
  double tmp;
  muestras_y = sizeConvolution(f.length, g.length);
  // double * y = (double *) malloc( sizeof(double) * muestras_y);
  ArrayDouble y = newArrayDouble(muestras_y);
  printf("Y.length: %d\n", muestras_y);
  for (i = 0; i < muestras_y; i++) {
    tmp = 0.0;
    i1 = i;
    for (j = 0; j < g.length; j++) {
      if( i1 >= 0 && i1 < f.length)
        tmp += (f.items[i1]*g.items[j]);
      i1 -= 1;
      y.items[i] = tmp;
    }
    // printf("Y.items[%d]: %f\n",i, y.items[i]);
  }
  return y;
}

/*
  Función para reducir la amplitud de un arreglo de muestras, no modifica el arreglo original
  en cambio retorna un arreglo nuevo con los valores reducidos a la mitad
  @param: samples //Un arreglo de muestras (16 bits por muestra)
*/
short *mediaAmplitud(short *samples, unsigned long cantidad)
{
  short *newSamples = malloc(sizeof(short) * cantidad);
  for (register int i = 0; i < cantidad; i++)
  {
    newSamples[i] = samples[i] >> 1;
  }
  return newSamples;
}


// double * convolucion(double * f, double * g, int size_f, int size_g){
//   int i, j, muestras_y, i1;
//   double tmp;
//   muestras_y = sizeConvolution(size_f, size_g);
//   double * y = (double *) malloc( sizeof(double) * muestras_y);
//   printf("Muestras Y: %d\n", muestras_y);
//   for (i = 0; i < muestras_y; i++) {
//     tmp = 0.0;
//     i1 = i;
//     for (j = 0; j < size_g; j++) {
//       if( i1 >= 0 && i1 < size_f)
//         tmp += (f[i1]*g[j]);
//       i1 -= 1;
//       y[i] = tmp;
//     }
//   }
//   return y;
// }



// short * convolucionShort(short * muestras, double * f, int cantMuestras, int size_f){
//   double * conv;
//   int sizeconv = sizeConvolution(cantMuestras, size_f);
//   short * convShort = (short *) malloc( sizeof(short) * sizeconv);
//   double * muestrasDouble = (double *) malloc( sizeof(double) * cantMuestras);
//   short menor_muestras = 0, mayor_muestras = 0;
//   for (int i = 0; i < cantMuestras; i++) {
//     if( muestras[i] < menor_muestras ) menor_muestras = muestras[i];
//     if( muestras[i] > mayor_muestras ) mayor_muestras = muestras[i];
//     muestrasDouble[i] = (double) muestras[i];
//     if(muestras[i] < menor_muestras){
//       menor_muestras = muestras[i];
//     }
//
//     // printf("muestras[%d] = %d\n",i, muestras[i] );
//     // printf("muestrasDouble[%d] = %f\n",i, muestrasDouble[i] );
//   }
//
//   for (int i = 0; i < size_f; i++) {
//     printf("f[%d] = %f\n",i, f[i] );
//   }
//
//
//
//
//   conv = convolucion(muestrasDouble, f, cantMuestras, size_f);
//   double menorConv = 0;
//   double mayorConv = 0;
//   for (int i = 0; i < sizeconv; i++) {
//     if(menorConv > conv[i]) menorConv = conv[i];
//     if(mayorConv < conv[i]) mayorConv = conv[i];
//     // if(conv[i] > 32767) conv[i] = 32767;
//   }
//
//   for (int i = 0; i < sizeconv; i++) {
//     conv[i] = (conv[i] - menorConv) / (mayorConv - menorConv) * (mayor_muestras - menor_muestras) + menor_muestras;
//
//     // convShort[i] = (short) conv[i];
//     convShort[i] = conv[i];
//     // printf("convolucion short conv[%d] = %f\n", i, conv[i]);
//     // printf("convolucion short convShort[%d] = %d\n", i, convShort[i]);
//   }
//   return convShort;
// }


ArrayDouble mapSamplesConvoluted(ArrayDouble muestras, ArrayDouble conv){
    ArrayDouble y2 = newArrayDouble(conv.length);
    double menorConv = 0;
    double mayorConv = 0;
    double mayor_muestras = 0;
    double menor_muestras = 0;
    for (int i = 0; i < conv.length; i++) {
      if(menorConv > conv.items[i]) menorConv = conv.items[i];
      if(mayorConv < conv.items[i]) mayorConv = conv.items[i];
      // if(conv[i] > 32767) conv[i] = 32767;
    }
    for (int i = 0; i < muestras.length; i++) {
      if( muestras.items[i] < menor_muestras ) menor_muestras = muestras.items[i];
      if( muestras.items[i] > mayor_muestras ) mayor_muestras = muestras.items[i];
    }
    for (int i = 0; i < conv.length; i++) {
      y2.items[i] = (conv.items[i] - menorConv) / (mayorConv - menorConv) * (mayor_muestras - menor_muestras) + menor_muestras;
      // y2.items[i] = conv.items[i];
    }
    return y2;
}

ArrayDouble mapToOne(ArrayDouble muestras){
  ArrayDouble out = newArrayDouble(muestras.length);
  for (int i = 0; i < muestras.length; i++) {
    out.items[i] = muestras.items[i] / 32767.0;
  }
  return out;
}

ArrayDouble mapFromOne(ArrayDouble muestras){
  ArrayDouble out = newArrayDouble(muestras.length);
  for (int i = 0; i < muestras.length; i++) {
    out.items[i] = muestras.items[i] * 32767.0;
  }
  return out;
}

ArrayShort multiplicarMuestras(ArrayShort a, ArrayShort b){
  int m = mayor(a.length, b.length);
  ArrayShort c = newArrayShort(m);

  for (int i = 0; i < m; i++) {
    if(a.length >= i && b.length >= i){
      // printf("Multiplicando!\n");
      // printf("c[%d] = %d * %d\n", i, a.items[i],  b.items[i]);
      c.items[i] = a.items[i] * b.items[i];

    }else if(a.length > i && b.length < i){
      c.items[i] = b.items[i];
      // printf("Es B!\n");
    }else{
      c.items[i] = a.items[i];
      // printf("Es A!\n");
    }
    //
    // if (c.items[i]  < -32768) c.items[i] = -32768;
    // if (c.items[i]  > 32767) c.items[i] = 32767;
  }
  return c;
}

ArrayDouble muestrear(ArrayDouble arr, int frecuenciaMuestreoMhz, WAVHeader wh){
  ArrayDouble out = newArrayDouble(arr.length);
  int frec = wh.SampleRate / frecuenciaMuestreoMhz;
  printf("frecuenciaMuestreoMhz:%d\n", frecuenciaMuestreoMhz);
  printf("SampleRate:%d\n", wh.SampleRate);
  printf("FRec:%d\n", frec);
  for (int i = 0; i < arr.length; i++) {
    out.items[i] = i % frec == 0 ? arr.items[i] : 0;
  }
  return out;
}


ArrayComplex transformadaFourier(ArrayDouble x){
  int N = x.length;
  double ang;
  double angeach;
  ArrayComplex X = newArrayComplex(N);

  for (int k = 0; k <= N-1; k++) {
    X.items[k] = newComplexNumber(0,0);
    // ang = - (2 * M_PI * k) / N
    for (int n = 0; n <= N-1; n++) {
      ang = - (2.0 * M_PI * k * n) / N;
      X.items[k].real += x.items[n] * cos(ang);
      X.items[k].imag += x.items[n] * sin(ang);
    }
  }
  return X;
}


ArrayDouble generarSeno(int items, int fm){
  ArrayDouble r = newArrayDouble(items);
  for(int i =0; i < items; i++ ){
    r.items[i] = sin(2*M_PI* i * 1/fm);
  } 
  return r;
}

ArrayDouble generarCoseno(int items, int fm){
  ArrayDouble r = newArrayDouble(items);
  for (int i = 0; i < items; i++)
  {
    r.items[i] = cos(2 * M_PI * i * 1 / fm);
  }
  return r;
}

// ArrayComplex transformadaFourierInversa(ArrayComplex X){
//   int N = X.length;
//   double ang;
//   double con;
//   ArrayComplex x = newArrayComplex(N);
//
//   for (int n = 0; n <= N-1; n++) {
//     for (int k = 0; k <= N-1; k++) {
//       ang = 2 * M_PI * k * n / N;
//       con = 1 / N;
//       x.items[n].real += newComplexNumber(con, 0) * X.items[k] * newComplexNumber(cos(ang), 0);
//       x.items[n].imag += newComplexNumber(con, 0) * X.items[k] * newComplexNumber(sin(ang), 0);
//     }
//   }
//   return x;
// }
