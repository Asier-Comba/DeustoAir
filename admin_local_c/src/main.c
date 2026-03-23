#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "auth.h"
#include "utils.h"
#include "config.h"
#include "database.h"
#include "globals.h"

#define RUTA_CONFIG "data/server.conf"

int main(void) {

    /* 1. Cargar configuracion */
    if (!cargarConfig(RUTA_CONFIG, &g_config)) {
        printf("[ERROR] No se pudo cargar la configuracion.\n");
        return 1;
    }

    /* 2. Inicializar base de datos */
    if (!db_init(g_config.db_path)) {
        printf("[ERROR] No se pudo inicializar la base de datos.\n");
        return 1;
    }

    /* 3. Bucle del menu principal (sin sesion) */
    int op;
    do {
        op = menu_principal();

        switch (op) {
            case 1:
                auth_iniciar_sesion();
                /* Si el login fue correcto, entrar al menu correspondiente */
                if (g_sesion.activo) {
                    if (g_sesion.usuario.es_admin)
                        menu_admin();
                    else
                        menu_usuario();
                } else {
                    pausarPantalla();
                }
                break;

            case 2:
                auth_registrar_usuario();
                pausarPantalla();
                break;

            case 0:
                printf("\nCerrando Deusto-Air. Hasta pronto!\n");
                break;

            default:
                printf("\n[ERROR] Opcion no valida.\n");
                pausarPantalla();
                break;
        }
    } while (op != 0);

    /* 4. Cerrar base de datos */
    db_close();
    return 0;
}
