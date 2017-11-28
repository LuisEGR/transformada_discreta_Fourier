#include <stdio.h>
#include "libs/dsp.h"
#include "libs/wav.h"

int main(int argc, char *argv[]) {
  FILE *entrada;
  MuestraMono muestra_mono;

  if (argc < 2) {
    printf("Uso: %s <entrada.wav>\n", argv[0]);
    return 0;
  }
  entrada = fopen(argv[1], "rb");
  WAVHeader hEntrada = readHeaderWAV(entrada);
  ArrayComplex tdf = transformadaFourier(entrada, hEntrada);
  printHeaderWAV(hEntrada);
  ArrayDouble mtdf = getMagFromArrayComplex(tdf);
    printf("MagnitudTDF: \n");
    printArrayDouble(mtdf);

  if (mtdf.items[70] > 0.5) {
    if (mtdf.items[121] > 0.5) {
      printf("Hay 1\n");
    }
    if (mtdf.items[134] > 0.5) {
      printf("Hay 2\n");
    }
    if (mtdf.items[148] > 0.5) {
      printf("Hay 3\n");
    }
  }

  if (mtdf.items[77] > 0.5) {
    if (mtdf.items[121] > 0.5) {
      printf("Hay 4\n");
    }
    if (mtdf.items[134] > 0.5) {
      printf("Hay 5\n");
    }
    if (mtdf.items[148] > 0.5) {
      printf("Hay 6\n");
    }
  }

  if (mtdf.items[85] > 0.5) {
    if (mtdf.items[121] > 0.5) {
      printf("Hay 7\n");
    }
    if (mtdf.items[134] > 0.5) {
      printf("Hay 8\n");
    }
    if (mtdf.items[148] > 0.5) {
      printf("Hay 9\n");
    }
  }
  fclose(entrada);
}
