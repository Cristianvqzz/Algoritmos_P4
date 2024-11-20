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

int main() {
    inicializar_semilla();


    printf("Insertar n elementos a un monticulo vacio:\n");
    tabla_insert(100,1);
    printf("Crear un monticulo a partir de un vector de n elementos:\n");
    tabla_crear(100,1);

    printf("Odenacion por Monticulos de minimos con vectores ascendentes:\n");
    tabla_ord(500,1,ascendente);
    printf("Odenacion por Monticulos de minimos con vectores descendentes:\n");
    tabla_ord(500,1,descendente);
    printf("Odenacion por Monticulos de minimos con vectores aleatorios:\n");
    tabla_ord(500,1,aleatorio);
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
    double sobrestimada,exacta,subestimada;

    sobrestimada = pow(n,1.2) ;
    exacta = n*log(n);
    subestimada = pow(n,0.8);

    for(i = 0; i < NUM_TABLAS; i++) {
        m = n;
        for(j = 0; j < 8; j++) {
            t = insert_time(m,k,aleatorio);
            printf("%12d%15.3f%15.7f%15.7f%15.7f\n",n,t,t/subestimada,t/exacta,t/sobrestimada);
            m *= 2;
        }
        printf("\n");
    }
}
void tabla_crear(int n,int k) {
    int i,j;
    int m;
    double t;
    double sobrestimada,exacta,subestimada;

    sobrestimada = pow(n,1.2) ;
    exacta = n;
    subestimada = pow(n,0.8);

    for(i = 0; i < NUM_TABLAS; i++) {
        m = n;
        for(j = 0; j < 8; j++) {
            t = insert_time(m,k,aleatorio);
            printf("%12d%15.3f%15.7f%15.7f%15.7f\n",n,t,t/subestimada,t/exacta,t/sobrestimada);
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

}