#ifndef CUT_H
#define CUT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include "memo.h"

void leerimagen(FILE* in,imagen* obj);
void maxMin(imagen* obj);
void recortar(imagen* obj,int h);
void imprimir(FILE* out,imagen* obj);
void graficarRecta1(int x1,int x2, int y1, int y2,double pen,imagen* obj);
void findPtos(imagen* obj);
void findPto3(imagen* obj);
void imprimirRecta2(FILE* out,imagen* obj);
void graficarRecta2(int x1,int x2, int y1, int y2,double pen,imagen* obj);
void graficarRecta3(int x1, int y1,double pen,imagen* obj);
void imprimirRecta3(FILE* out,imagen* obj);
void findPto2y4(imagen* obj);
void esqueleto(imagen* obj,FILE* outesq);
void graficaA(imagen* obj);
void graficaB(imagen* obj);
void graficaC(imagen* obj);
void graficaD(imagen* obj);
//ALEATORIO

void randpto1(random* rd,imagen* obj);
void randpto2(random* rd,imagen* obj);
void randpto3(random* rd,imagen* obj);
void randpto4(random* rd,imagen* obj);
void randpto5(random* rd,imagen* obj);
void randw(random* rd);
void refill(imagen* obj,random* rd);
void printRefill(imagen* obj,random* rd,FILE* out);
void params(imagen* obj,random* rd,metrica* m);
void accuracy(metrica* m);
void insertion_sort(individuo* s,int n);
void swap(individuo *e1,individuo *e2);
void angleLength(imagen* obj,int j);

//algoritmo de optimizacion
void genetico(int j);
void generatePob(imagen* obj, random* rd,individuo *ind,metrica* m);
void sortPob(individuo *ind);
void seleccionCruce(individuo *ind);
void evaluar(individuo *ind,imagen* obj,random* rd,metrica* m);
void best(individuo *ind,mejor *mej);
void esqbest(imagen* obj,mejor *mej,random *rd);


#endif // LECTURABIN_H
