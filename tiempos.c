//
// Created by daortiz on 15/11/24.
//

#include "tiempos.h"

double microsegundos() {
    struct timeval t;

    if(gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double ord_time_bajo(int n,int k,void (*inicializar) (int v[],int n),void (*ordenar) (int v[],int n)){
    double t,t1,t2,ta,tb;
    int *v;
    int i;

    v = malloc(n*sizeof(int));

    ta = microsegundos();
    for (i = 0; i < k; i++) {
        inicializar(v,n);
        ordenar(v,n);
    }
    tb = microsegundos();
    t1 = tb - ta;
    if (t1 < 500) {
        printf("k no valida t1 < 500 \n");
        free(v);
        return t1;
    }
    ta = microsegundos();
    for (i = 0; i < k; i++) {
        inicializar(v,n);
    }
    tb = microsegundos();
    t2 = tb - ta;
    t = t1 - t2;
    if (t < 500) {
        printf("k no valida t < 500 \n");
        free(v);
        return t;
    }
    free(v);
    return t / k;
}
double ord_time(int n,int k,void (*inicializar) (int v[],int n),void (*ordenar) (int v[],int n)) {
    double t,t1,t2;
    int *v;

    v = malloc(n*sizeof(int));
    inicializar(v,n);
    t1 = microsegundos();
    ordenar(v,n);
    t2 = microsegundos();
    t = t2 - t1;
    free(v);
    if (t < 500) {
        printf("%-12d*",k);
        t = ord_time_bajo(n,k,inicializar,ordenar);
    }else {
        printf("%-12d*",1);
    }
    return t;
}
double insert_time_bajo(int n,int k,void (*inicializar) (int v[],int n)) {
    double t,t1,t2,ta,tb;
    int *v;
    pmonticulo m;

    m = malloc(sizeof(struct monticulo));
    v = malloc(n*sizeof(int));

    ta = microsegundos();
    for (int i = 0; i < k; i++) {
        inicializar(v,n);
        iniMonticulo(m);
        for (int j = 0; j < n; j++) {
            insertarMonticulo(m,v[j]);
        }
    }
    tb = microsegundos();
    t1 = tb - ta;
    if (t1 < 500) {
        printf("k no valida t1 < 500 \n");
        free(v);
        free(m);
        return t1;
    }
    ta = microsegundos();
    for (int i = 0; i < k; i++) {
        inicializar(v,n);
        iniMonticulo(m);
    }
    tb = microsegundos();
    t2 = tb - ta;
    t = t1 - t2;
    if (t < 500) {
        printf("k no valida t < 500 \n");
        free(v);
        free(m);
        return t;
    }
    free(v);
    free(m);
    return t / k;
}
double insert_time(int n,int k,void (*inicializar) (int v[],int n)) {
    double t,t1,t2;
    int *v;
    pmonticulo m;

    v = malloc(n*sizeof(int));
    m = malloc(sizeof(struct monticulo));

    inicializar(v,n);
    iniMonticulo(m);
    t1 = microsegundos();
    for (int i = 0; i < n; i++) {
        insertarMonticulo(m,v[i]);
    }
    t2 = microsegundos();
    t = t2 - t1;

    free(v);
    free(m);

    if (t < 500) {
        printf("%-12d*",k);
        t = insert_time_bajo(n,k,inicializar);
    }else {
        printf("%-12d*",1);
    }
    return t;
}
double crear_time_bajo(int n,int k,void (*inicializar) (int v[],int n)) {
    double t,t1,t2,ta,tb;
    int *v;
    pmonticulo m;
    //Preguntar si es necesacio inimonticulo para crear
    v = malloc(n*sizeof(int));
    m = malloc(sizeof(struct monticulo));

    ta = microsegundos();
    for (int i = 0; i < k; i++) {
        inicializar(v,n);
        iniMonticulo(m);
        for (int j = 0; j < n; j++) {
            crearMonticulo(m,v,n);
        }
    }
    tb = microsegundos();
    t1 = tb - ta;
    if (t1 < 500) {
        printf("k no valida t1 < 500 \n");
        free(v);
        free(m);
        return t1;
    }
    ta = microsegundos();
    for (int i = 0; i < k; i++) {
        inicializar(v,n);
        iniMonticulo(m);
    }
    tb = microsegundos();
    t2 = tb - ta;
    t = t1 - t2;
    if (t < 500) {
        printf("k no valida t < 500 \n");
        free(v);
        free(m);
        return t;
    }
    free(v);
    free(m);
    return t / k;
}
double crear_time(int n,int k,void (*inicializar) (int v[],int n)) {
    double t,t1,t2;
    int *v;
    pmonticulo m;

    v = malloc(n*sizeof(int));
    m = malloc(sizeof(struct monticulo));

    inicializar(v,n);
    iniMonticulo(m);
    t1 = microsegundos();
    for (int i = 0; i < n; i++) {
        crearMonticulo(m,v,n);
    }
    t2 = microsegundos();
    t = t2 - t1;

    free(v);
    free(m);

    if (t < 500) {
        printf("%-12d*",k);
        t = crear_time_bajo(n,k,inicializar);
    }else {
        printf("%-12d*",1);
    }
    return t;
}