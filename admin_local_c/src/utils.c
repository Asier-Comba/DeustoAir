/*
 * utils.c
 *
 *  Created on: 9 mar 2026
 *      Author: asier.comba
 */


#include <stdio.h>
#include "utils.h"

void limpiarBuffer(void) {
    while (getchar() != '\n');
}

void pausarPantalla(void) {
    printf("\nPulsa ENTER para continuar...");
    getchar();
}
