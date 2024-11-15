#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#define TAM 256000
#define NUM_TABLAS 1

struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo *pmonticulo;

void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m,int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m,int v[],int n);
void flotar(pmonticulo m,int i);
void hundir(pmonticulo m,int i);
void OrdenarPorMonticulos(int v[],int n);

double microsegundos();
void inicializar_semilla();
void aleatorio(int v[],int n);
void ascendente(int v[], int n);
void descendente(int v[], int n);
void intercambiar(int* i,int* j);

int main() {

}
void iniMonticulo(pmonticulo m) {
    m->ultimo = -1;
}
void insertarMonticulo(pmonticulo m,int x) {

    if(m->ultimo == TAM-1) {
        printf("Monticulo lleno\n");
    }else {
        m->ultimo++;
        m->vector[m->ultimo] = x;
        flotar(m,m->ultimo);
    }
}
void quitarMenor(pmonticulo m) {
    int x;

    if(m->ultimo == -1) {
        printf("Monticulo vacio\n");
    }else {
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo--;
        if(m->ultimo > -1) hundir(m,0);
    }
}
int consultarMenor(const pmonticulo m) {
    return m->vector[0];
}
void crearMonticulo(pmonticulo m,int v[],int n) {
    int i;
    for(i = 0; i < n; i++) {
        m->vector[i] = v[i];
    }
    m->ultimo = n-1;
    for(i = (TAM-1)/2; i >= 0; i--) {
        hundir(m,i);
    }
}
void flotar(pmonticulo m,int i);
void hundir(pmonticulo m,int i);

double microsegundos() {
    struct timeval t;

    if(gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
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
void OrdenarPorMonticulos(int v[],int n) {
    pmonticulo m;
    int i;

    iniMonticulo(m);
    crearMonticulo(m,v,n);

    for(int i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
}
void intercambiar(int* i,int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

