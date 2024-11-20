//
// Created by daortiz on 15/11/24.
//

#ifndef TIEMPOS_H
#define TIEMPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "monticulos.h"

double microsegundos();
double ord_time(int n,int k,void (*inicializar) (int v[],int n),void (*ordenar) (int v[],int n));
double insert_time(int n,int k,void (*inicializar) (int v[],int n));
double crear_time(int n,int k,void (*inicializar) (int v[],int n));


#endif //TIEMPOS_H
