#include <stdio.h>
#include "utils.h"

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarPantalla(void) {
    printf("\nPulsa ENTER para continuar...");
    fflush(stdout);
    getchar();
}

void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
