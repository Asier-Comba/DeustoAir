#include <stdio.h>

int main(void) {
    int opcion;
    int leido;

    do {
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
            while (getchar() != '\n');
            opcion = -1;
        } else {
            while (getchar() != '\n');

            switch (opcion) {
                case 1:
                    printf("\nHas elegido iniciar sesion.\n");
                    break;

                case 2:
                    printf("\nHas elegido registrar usuario.\n");
                    break;

                case 0:
                    printf("\nSaliendo...\n");
                    break;

                default:
                    printf("\n[ERROR] Opcion no valida.\n");
            }
        }

        if (opcion != 0) {
            printf("\nPulsa ENTER para continuar...");
            getchar();
        }

    } while (opcion != 0);

    return 0;
}
