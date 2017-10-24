#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "filtros.h"

double hzToRad(double hz){
  return 2 * M_PI * hz;
}

//Para el ejemplo que está en el libro (Filtro pasabajas ideal)
double * obtenerMuestrasPasabajas(int cantidad, float fc, float fmuestreo){
  //fc = frecuencia de corte en Khz
  // float frecuenciaMuestreo = 44100 / 1000;//en Khz
  float Wc = (2*M_PI*fc) / fmuestreo;//frecuencia de Corte
  printf("Wc: %f\n", Wc);
  float muestraTmp;

  double * muestras;
  muestras = (double *) malloc(sizeof(double) * cantidad);

  for(int n = 0; n < cantidad; n++){
    if(n != 0){
      muestraTmp = sin( Wc*n ) / (M_PI*n);
    }else{ //n = 0
      muestraTmp = Wc / M_PI;
    }
    muestras[n] = muestraTmp;
  }
  return muestras;
}


/*
  cantidad: Cuantas muestras se desean
  fc: Frecuencia de corte
  fm: Frecuencia de muestreo
*/
double * obtenerMuestrasPasabajasRC(int cantidad, float fc, float fm){
  int u;
  float RC = 1 / (2 * M_PI * fc);
  // float RC = 1000;
  float t = 1.0 / fm;
  //Reservo memoria
  double * muestras = (double *)malloc(sizeof(double) * cantidad);
  printf("RC: %f ... 1/RC: %f\n", RC, 1/RC);
  for (int i = 0; i < cantidad; i++) {
    u = i < 0 ? 0 : 1;//Heviside u(t)
    //Respuesta al impulso
    muestras[i] = (1 / RC) * exp(-(t*i)/RC) * u;
    // muestras[i] = exp(-(t*i)/RC) * u;
  }
  return muestras;
}
