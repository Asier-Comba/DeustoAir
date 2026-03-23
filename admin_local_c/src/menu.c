#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "globals.h"
#include "utils.h"
#include "auth.h"
#include "mediciones.h"
#include "import_datos.h"
#include "usuarios.h"
#include "perfiles.h"
#include "logs_app.h"
#include "database.h"
#include "config.h"

/* ================================================================== */
/*  HELPERS                                                            */
/* ================================================================== */

static void cabecera(const char *titulo) {
    printf("\n==============================\n");
    printf("  %s\n", titulo);
    printf("==============================\n");
}

static int leer_opcion(void) {
    int op;
    printf("\nOpcion: ");
    fflush(stdout);
    int leido = scanf("%d", &op);
    limpiarBuffer();
    if (leido != 1) return -1;
    return op;
}

/* ================================================================== */
/*  MENU PRINCIPAL (sin sesion)                                        */
/* ================================================================== */
int menu_principal(void) {
    cabecera("DEUSTO-AIR v1.0");
    printf("1) Iniciar sesion\n");
    printf("2) Registrar usuario\n");
    printf("0) Salir\n");
    return leer_opcion();
}

/* ================================================================== */
/*  MENU ESTADISTICAS — USUARIO NORMAL (con permisos)                 */
/* ================================================================== */
void menu_estadisticas_usuario(void) {
    Perfil *p = &g_sesion.usuario.perfil;
    int op;

    do {
        cabecera("ESTADISTICAS");

        /* Solo se muestran las opciones permitidas por el perfil */
        if (p->ver_ultima_medicion) printf("1) Ultima medicion por estacion\n");
        if (p->ver_historico)       printf("2) Historico por municipio\n");
        if (p->ver_ranking)         printf("3) Ranking por contaminante\n");
        if (p->ver_por_municipio)   printf("4) Media por municipio\n");
        if (p->ver_por_provincia)   printf("5) Media por provincia\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1:
                if (p->ver_ultima_medicion) { med_ultima_por_estacion(); pausarPantalla(); }
                else printf("[ERROR] Sin permiso.\n");
                break;
            case 2:
                if (p->ver_historico) { med_historico_municipio(); pausarPantalla(); }
                else printf("[ERROR] Sin permiso.\n");
                break;
            case 3:
                if (p->ver_ranking) { med_ranking_contaminante(); pausarPantalla(); }
                else printf("[ERROR] Sin permiso.\n");
                break;
            case 4:
                if (p->ver_por_municipio) { med_historico_municipio(); pausarPantalla(); }
                else printf("[ERROR] Sin permiso.\n");
                break;
            case 5:
                if (p->ver_por_provincia) { med_media_por_provincia(); pausarPantalla(); }
                else printf("[ERROR] Sin permiso.\n");
                break;
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ================================================================== */
/*  MENU USUARIO NORMAL (tras login sin admin)                         */
/* ================================================================== */
void menu_usuario(void) {
    int op;
    do {
        cabecera("MENU USUARIO");
        printf("  Hola, %s  [Perfil: %s]\n",
               g_sesion.usuario.username,
               g_sesion.usuario.perfil.nombre[0]
                   ? g_sesion.usuario.perfil.nombre : "Basico");
        printf("------------------------------\n");
        printf("1) Consultar datos de calidad\n");
        printf("2) Cambiar mi contrasena\n");
        printf("0) Cerrar sesion\n");

        op = leer_opcion();

        switch (op) {
            case 1:
                menu_estadisticas_usuario();
                break;
            case 2:
                printf("\n");
                usuarios_cambiar_password(g_sesion.usuario.username);
                pausarPantalla();
                break;
            case 0:
                log_registrar(g_sesion.usuario.username, "Cierre de sesion");
                memset(&g_sesion, 0, sizeof(g_sesion));
                printf("\n[OK] Sesion cerrada.\n");
                break;
            default:
                printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ================================================================== */
/*  SUBMENUS DEL ADMINISTRADOR                                         */
/* ================================================================== */

/* ── Gestion de datos (importacion y estaciones) ───────────────── */
void menu_gestion_datos(void) {
    int op;
    do {
        cabecera("GESTION DE DATOS");
        printf("1) Importar datos desde CSV\n");
        printf("2) Ver estaciones registradas\n");
        printf("3) Borrar todos los datos\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1:
                printf("\nImportando desde: %s\n", g_config.data_path);
                import_csv(g_config.data_path);
                pausarPantalla();
                break;
            case 2:
                import_ver_estaciones();
                pausarPantalla();
                break;
            case 3: {
                printf("\n[AVISO] Se borraran TODAS las mediciones y estaciones.\n");
                printf("Continuar? (s/n): ");
                char c[4];
                if (fgets(c, sizeof(c), stdin) && (c[0] == 's' || c[0] == 'S')) {
                    if (db_borrar_datos()) {
                        printf("[OK] Datos borrados.\n");
                        log_registrar(g_sesion.usuario.username, "BD de datos borrada");
                    }
                } else {
                    printf("[Cancelado]\n");
                }
                pausarPantalla();
                break;
            }
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ── Gestion de usuarios ────────────────────────────────────────── */
void menu_gestion_usuarios(void) {
    int op;
    do {
        cabecera("GESTION DE USUARIOS");
        printf("1) Listar usuarios\n");
        printf("2) Asignar perfil a usuario\n");
        printf("3) Activar / desactivar usuario\n");
        printf("4) Cambiar contrasena de usuario\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1:
                usuarios_listar();
                pausarPantalla();
                break;
            case 2:
                usuarios_cambiar_perfil();
                pausarPantalla();
                break;
            case 3:
                usuarios_toggle_activo();
                pausarPantalla();
                break;
            case 4: {
                char usr[MAX_NOMBRE];
                printf("Usuario: "); fflush(stdout);
                if (fgets(usr, sizeof(usr), stdin)) {
                    usr[strcspn(usr, "\r\n")] = '\0';
                    usuarios_cambiar_password(usr);
                }
                pausarPantalla();
                break;
            }
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ── Gestion de perfiles (feedback profesor) ────────────────────── */
void menu_gestion_perfiles(void) {
    int op;
    do {
        cabecera("GESTION DE PERFILES");
        printf("1) Listar perfiles y permisos\n");
        printf("2) Crear nuevo perfil\n");
        printf("3) Modificar permisos de un perfil\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1:
                perfiles_listar();
                pausarPantalla();
                break;
            case 2:
                perfiles_crear();
                pausarPantalla();
                break;
            case 3:
                perfiles_modificar();
                pausarPantalla();
                break;
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ── Estadisticas completas (admin ve todo) ─────────────────────── */
void menu_estadisticas_admin(void) {
    int op;
    do {
        cabecera("ESTADISTICAS");
        printf("1) Ultima medicion por estacion\n");
        printf("2) Historico por municipio\n");
        printf("3) Ranking por contaminante\n");
        printf("4) Media por provincia\n");
        printf("5) Alertas: valores sobre umbral\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1: med_ultima_por_estacion();  pausarPantalla(); break;
            case 2: med_historico_municipio();  pausarPantalla(); break;
            case 3: med_ranking_contaminante(); pausarPantalla(); break;
            case 4: med_media_por_provincia();  pausarPantalla(); break;
            case 5: med_alertas_superacion();   pausarPantalla(); break;
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ── Sistema (logs, config, sesion) ─────────────────────────────── */
void menu_sistema(void) {
    int op;
    do {
        cabecera("SISTEMA");
        printf("1) Ver registro de logs\n");
        printf("2) Ver configuracion\n");
        printf("0) Volver\n");

        op = leer_opcion();

        switch (op) {
            case 1: log_mostrar();             pausarPantalla(); break;
            case 2: mostrarConfig(&g_config);  pausarPantalla(); break;
            case 0: break;
            default: printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}

/* ================================================================== */
/*  MENU ADMINISTRADOR (tras login con es_admin=1)                    */
/* ================================================================== */
void menu_admin(void) {
    int op;
    do {
        cabecera("MENU ADMINISTRADOR");
        printf("  Hola, %s\n", g_sesion.usuario.username);
        printf("------------------------------\n");
        printf("1) Gestion de datos\n");
        printf("2) Gestion de usuarios\n");
        printf("3) Gestion de perfiles\n");
        printf("4) Estadisticas\n");
        printf("5) Sistema\n");
        printf("0) Cerrar sesion\n");

        op = leer_opcion();

        switch (op) {
            case 1: menu_gestion_datos();    break;
            case 2: menu_gestion_usuarios(); break;
            case 3: menu_gestion_perfiles(); break;
            case 4: menu_estadisticas_admin(); break;
            case 5: menu_sistema();          break;
            case 0:
                log_registrar(g_sesion.usuario.username, "Cierre de sesion");
                memset(&g_sesion, 0, sizeof(g_sesion));
                printf("\n[OK] Sesion cerrada.\n");
                break;
            default:
                printf("[ERROR] Opcion no valida.\n");
        }
    } while (op != 0);
}
