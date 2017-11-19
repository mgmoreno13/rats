#ifndef MEMO_H
#define MEMO_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>



typedef struct iman{
int nr;
int nc;
char str[50];
int** img;
int** rec;
int** esq;
int* recta1;//x=(1/m)*(y-y1)+x1
int* recta2;//P1 A P3
int* recta3;//perpendicular a recta 1 y pasa por el punto 3(pendiente y punto)
int* rectaA;
int* rectaB;
int* rectaC;
int* rectaD;
int superior[2];
int inferior[2];
int izquierdo[2];
int derecho[2];
int ngrises;
int rfil;
int rcol;
int p1[2];
int p2[2];
int p11[2];
int p111[2];
int p5[2];
int p55[2];
int p555[2];
int p3[2];
int p4[2];
int rizq[2];//punto donde se recorto por margen izquierda
int rder[2];//punto donde se recorto por margen derecho
double penrect1;
double penrect2;
double penA;
double penB;
double penC;
double penD;
double L1;
double L2;
double L3;
double L4;
double A1;
double A2;
double A3;
double A4;
int interseccion[2];
}imagen;

typedef struct {
int r;
int w;
int** fill; 
}random;

typedef struct {
int TP;
int TN;
int FP; 
int FN;
double accur;
}metrica;

typedef struct {
int p1[2];
int p2[2];
int p3[2];
int p4[2];
int p5[2];
int w;
double fitness;
double pos;//posicion
}individuo;


typedef struct {
int p1[2];
int p2[2];
int p3[2];
int p4[2];
int p5[2];
int w;
double fitness;
}mejor;

int **createMatrixint(int nr, int nc);
void freeOBJ(imagen* OBJ);
void freeRD(random* rd);


#endif // LECTURABIN_H
