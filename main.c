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

double ord_time(int n,int k,void (*inicializar) (int v[],int n));
void tabla(int n,int k,void (*inicializar) (int v[],int n),void (*ordenar) (int v[],int n));

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

    for(i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
}
void intercambiar(int* i,int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}
double ord_time(int n,int k,void (*inicializar) (int v[],int n)) {
    double t,t1,t2,ta,tb;
    int *v;
    int i;

    v = malloc(n*sizeof(int));
    inicializar(v,n);
    t1 = microsegundos();
    OrdenarPorMonticulos(v,n);
    t2 = microsegundos();
    t = t2 - t1;

    if (t < 500) {
        printf("%-12d*",k);
        ta = microsegundos();
        for (i = 0; i < k; i++) {
            inicializar(v,n);
            OrdenarPorMonticulos(v,n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        if (t1 < 500) {
            printf("k no valida t1 < 500 \n");
            free(v);
            return 0.0;
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
            return 0.0;
        }
        t /= k;
    }else {
        printf("%-12d*",1);
    }
    free(v);
    return t;
}
void tabla_ord(int n,int k,void (*inicializar) (int v[],int n)) {
    double t;
    double sobrestimada,exacta,subestimada;

    if(inicializar == ascendente) {
        sobrestimada = 0.0;
        exacta = 0.0;
        subestimada = 0.0;
    }else if(inicializar == descendente) {
        sobrestimada = 0.0;
        exacta = 0.0;
        subestimada = 0.0;
    }else if(inicializar == aleatorio) {
        sobrestimada = 0.0;
        exacta = 0.0;
        subestimada = 0.0;
    }else {
        printf("Inicializacion no valida\n");
        return;
    }
    t = ord_time(n,k,inicializar);
    printf("%12d%15.3f%15.7f%15.7f%15.7f\n",n,t,t/subestimada,t/exacta,t/sobrestimada);
}