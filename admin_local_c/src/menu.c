/*
 * menu.c
 *
 *  Created on: 9 mar 2026
 *      Author: asier.comba
 */


#include <stdio.h>
#include "menu.h"
#include "utils.h"

int mostrarMenuPrincipal(void) {
    int opcion;
    int leido;

    printf("\n==============================\n");
    printf("DEUSTO-AIR\n");
    printf("==============================\n");
    printf("1) Iniciar sesion\n");
    printf("2) Registrar usuario\n");
    printf("0) Salir\n");
    printf("Opcion: ");
    fflush(stdout);

    leido = scanf("%d", &opcion);

    if (leido != 1) {
        printf("\n[ERROR] Entrada no valida. Debes introducir un numero.\n");
        limpiarBuffer();
        return -1;
    }

    limpiarBuffer();
    return opcion;
}
