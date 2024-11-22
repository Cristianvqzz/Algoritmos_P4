#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include "tiempos.h"
#include "monticulos.h"

#define NUM_TABLAS 1

void inicializar_semilla();
void aleatorio(int v[],int n);
void ascendente(int v[], int n);
void descendente(int v[], int n);
void cota_ord(int n,int k,void (*inicializar) (int v[],int n));
void tabla_ord(int n,int k,void (*inicializar) (int v[],int n));
void tabla_insert(int n,int k);
void tabla_crear(int n,int k);
void mostrar(int v[],int n);
bool ordenado(int v[],int n);
void test();
void test_crear(int v[],int n);
void test_insertar(int v[],int n);
void test_ord(int v[],int n);
void adaptadorMin(int v[],int n);

int main() {
    inicializar_semilla();

   // test();

    /*printf("Insertar n elementos a un monticulo vacio:\n");
    tabla_insert(2000,10);*/
    printf("Crear un monticulo a partir de un vector de n elementos:\n");
    tabla_crear(2000,100);

    /*printf("Odenacion por Monticulos de minimos con vectores ascendentes:\n");
    tabla_ord(500,1,ascendente);
    printf("Odenacion por Monticulos de minimos con vectores descendentes:\n");
    tabla_ord(500,1,descendente);
    printf("Odenacion por Monticulos de minimos con vectores aleatorios:\n");
    tabla_ord(500,1,aleatorio);*/
}

void inicializar_semilla() {
    srand(time(NULL));
}
void aleatorio(int v[],int n) {
    int i, m = 2*n+1;
    for (i=0; i<n; i++) {
        v[i] = (rand() % m) - n;
    }
}
void ascendente(int v[], int n) {
    int i;
    for (i=0; i<n; i++) {
        v[i] = i;
    }
}
void descendente(int v[], int n) {
    int i;
    for (i = 0; i< n; i++) {
        v[i] = n - i - 1;
    }
}
void cota_ord(int n,int k,void (*inicializar) (int v[],int n)) {
    double t;
    double sobrestimada,exacta,subestimada;

    if(inicializar == ascendente) {
        sobrestimada = 1.0;
        exacta = 1.0;
        subestimada = 1.0;
    }else if(inicializar == descendente) {
        sobrestimada = 1.0;
        exacta = 1.0;
        subestimada = 1.0;
    }else if(inicializar == aleatorio) {
        sobrestimada = 1.0;
        exacta = 1.0;
        subestimada = 1.0;
    }else {
        printf("Inicializacion no valida\n");
        return;
    }
    t = ord_time(n,k,inicializar,OrdenarPorMonticulos);
    printf("%12d%15.3f%15.7f%15.7f%15.7f\n",n,t,t/subestimada,t/exacta,t/sobrestimada);
}
void tabla_ord(int n,int k,void (*inicializar) (int v[],int n)) {
    int i ,j;
    int m;

    for(i = 0; i < NUM_TABLAS ; i++) {
        m = n;
        for(j = 0; j < 8; j++) {
            cota_ord(m,k,inicializar);
            m *= 2;
        }
        printf("\n");
    }
}
void tabla_insert(int n,int k) {
    int i,j;
    int m;
    double t;

    for(i = 0; i < NUM_TABLAS; i++) {
        m = n;
        for(j = 0; j < 8; j++) {
            t = insert_time(m,k,aleatorio);
            printf("%12d%15.3f%15.7f%15.7f%15.7f\n",m,t,t/pow(m,0.8),t/(m*log(m)),t/pow(m,1.2));
            m *= 2;
        }
        printf("\n");
    }
}
void tabla_crear(int n,int k) {
    int i,j;
    int m;
    double t;

    for(i = 0; i < NUM_TABLAS; i++) {
        m = n;
        for(j = 0; j < 8; j++) {
            t = crear_time(m,k,aleatorio);
            printf("%12d%15.3f%15.7f%15.7f%15.7f\n",m,t,t/pow(m,0.8),t/m,t/pow(m,1.2));
            m *= 2;
        }
        printf("\n");
    }
}
bool ordenado(int v[],int n) {
    int i;
    for(i = 0;i < n-1; i++) {
        if(v[i] > v[i+1]) return false;
    }
    return true;
}
void mostrar(int v[],int n) {
    int i;

    for(i = 0;i < n; i++) {
        printf("%d ",v[i]);
    }
    printf("\n");
}
void test() {
    int v[20];

    test_ord(v,20);
    test_crear(v,20);
    test_insertar(v,20);
}
void test_crear(int v[],int n) {
    struct monticulo m;

    printf("Monticulo Creado a partir de un vector ordenado ascendentemente:\n");
    ascendente(v,n);
    crearMonticulo(&m,v,n);
    mostrar(m.vector,n);

    printf("Monticulo Creado a partir de un vector ordenado descendentemente:\n");
    descendente(v,n);
    crearMonticulo(&m,v,n);
    mostrar(m.vector,n);

    printf("Monticulo Creado a partir de un vector aleatorio:\n");
    aleatorio(v,n);
    crearMonticulo(&m,v,n);
    mostrar(m.vector,n);
}
void test_insertar(int v[],int n) {
    int i;
    struct monticulo m;

    printf("Vector ordenado ascendente:\n");
    ascendente(v,n);
    mostrar(v,n);
    iniMonticulo(&m);
    for(i = 0;i < n; i++) {
        insertarMonticulo(&m,v[i]);
    }
    printf("Monticulo resultante al insertar los elementos del vector:\n");
    mostrar(m.vector,m.ultimo+1);

    printf("Vector ordenado descendente:\n");
    descendente(v,n);
    mostrar(v,n);
    iniMonticulo(&m);
    for(i = 0;i < n; i++) {
        insertarMonticulo(&m,v[i]);
    }
    printf("Monticulo resultante al insertar los elementos del vector:\n");
    mostrar(m.vector,m.ultimo+1);

    printf("Vector aleatorio:\n");
    aleatorio(v,n);
    mostrar(v,n);
    iniMonticulo(&m);
    for(i = 0;i < n; i++) {
        insertarMonticulo(&m,v[i]);
    }
    printf("Monticulo resultante al insertar los elementos del vector:\n");
    mostrar(m.vector,m.ultimo+1);
}
void test_ord(int v[],int n) {

    printf("Vector ordenado ascendente:\n");
    ascendente(v,n);
    mostrar(v,n);
    printf("Vector tras ordenacion por monticulos:\n");
    OrdenarPorMonticulos(v,n);
    mostrar(v,n);

    printf("Vector ordenado descendente:\n");
    descendente(v,n);
    mostrar(v,n);
    printf("Vector tras ordenacion por monticulos:\n");
    OrdenarPorMonticulos(v,n);
    mostrar(v,n);

    printf("Vector aleatorio:\n");
    aleatorio(v,n);
    mostrar(v,n);
    printf("Vector tras ordenacion por monticulos:\n");
    OrdenarPorMonticulos(v,n);
    mostrar(v,n);
}

