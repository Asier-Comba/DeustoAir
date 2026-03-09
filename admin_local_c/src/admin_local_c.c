/*
 ============================================================================
 Name        : admin_local_c.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
    int opcion;

    do {
        printf("\n==============================\n");
        printf("DEUSTO-AIR\n");
        printf("==============================\n");
        printf("1) Iniciar sesion\n");
        printf("2) Registrar usuario\n");
        printf("0) Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Has elegido iniciar sesion.\n");
                break;
            case 2:
                printf("Has elegido registrar usuario.\n");
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}

