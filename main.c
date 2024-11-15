#include <stdio.h>

#define TAM 256000

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
void intercambiar(int* i, int* j);
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
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m,int v[],int n);
void flotar(pmonticulo m,int i) {

    while(i > 1 && m->vector[i/2] < m->vector[i]) {
        intercambiar(&m->vector[i/2],&m->vector[i]);
        i = i/2;;
    }
}
void hundir(pmonticulo m,int i) {

    int hi = 2 * i + 1;
    int hd = 2 * i + 2;
    int j = i;

    if (hd < m->ultimo && m->vector[hd] > m->vector[i])
        i = hd;
    else if (hi < m->ultimo && m->vector[hi] > m->vector[i])
        i = hi;
    while(j!=i) {
        intercambiar(&m->vector[hi],&m->vector[i]);
        j++;
    }
}

















