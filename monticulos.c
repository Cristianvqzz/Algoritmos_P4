//
// Created by daortiz on 15/11/24.
//

#include "monticulos.h"

void intercambiar(int* i,int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}
void flotar(pmonticulo m,int i) {

    while(i > 0 && m->vector[i-1/2] > m->vector[i]) {
        intercambiar(&m->vector[i-1/2],&m->vector[i]);
        i = i-1/2;
    }
}
void hundir(pmonticulo m,int i) {
    int hi,hd,j;

    do {
        hi = 2 * i + 1;
        hd = 2 * i + 2;
        j = i;

        if (hd < m->ultimo && m->vector[hd] > m->vector[i])
            i = hd;
        if (hi < m->ultimo && m->vector[hi] > m->vector[i])
            i = hi;
        intercambiar(&m->vector[hi],&m->vector[i]);
    }while (i != j);

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

    if(m->ultimo == -1) {
        printf("Monticulo vacio\n");
    }else {
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
void OrdenarPorMonticulos(int v[],int n) {
    pmonticulo m;
    int i;

    iniMonticulo(m);
    crearMonticulo(m,v,n);

    for(i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
}