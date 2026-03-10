#include <stdio.h>
#include "menu.h"
#include "auth.h"
#include "utils.h"

int main(void) {
    int opcion;

    do {
        opcion = mostrarMenuPrincipal();

        switch (opcion) {
            case 1:
                iniciarSesion();
                break;

            case 2:
                registrarUsuario();
                break;

            case 0:
                printf("\nSaliendo...\n");
                break;

            default:
                printf("\n[ERROR] Opcion no valida.\n");
        }

        if (opcion != 0) {
            pausarPantalla();
        }

    } while (opcion != 0);

    return 0;
}
//Prueba commit