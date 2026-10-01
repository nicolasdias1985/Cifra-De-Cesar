/* Funcoes que calculam as sequencias numericas: PA, PG, Fibonacci e Primos */

#include "sequencias.h"

int sequencia(int tipo, int i) {
    int k;

    if (tipo == 1) {
        return 1 + 2 * i;              /* PA: 1, 3, 5, 7... */
    }

    if (tipo == 2) {                   /* PG: 1, 2, 4, 8... */
        int r = 1;
        for (k = 0; k < i; k++) {
            r = r * 2;
        }
        return r;
    }

    if (tipo == 3) {                   /* Fibonacci: 1, 1, 2, 3, 5... */
        int a = 1, b = 1, aux;
        for (k = 0; k < i; k++) {
            aux = a + b;
            a = b;
            b = aux;
        }
        return a;
    }

    /* Primos: 2, 3, 5, 7, 11... */
    int contados = 0, num = 1, d, primo;
    while (contados <= i) {
        num++;
        primo = 1;
        for (d = 2; d * d <= num; d++) {
            if (num % d == 0) {
                primo = 0;
                break;
            }
        }
        if (primo == 1) {
            contados++;
        }
    }
    return num;
}
