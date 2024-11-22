//Daniel Ortiz Sierra daniel.ortiz@udc.es
//Cristian Vázquez Seijas cristian.vazquez.seijas@udc.es
#ifndef MONTICULOS_H
#define MONTICULOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;

void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m,int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m,int v[],int n);
void OrdenarPorMonticulos(int v[],int n);
#endif //MONTICULOS_H
