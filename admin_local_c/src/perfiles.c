#include <stdio.h>
#include <string.h>
#include "perfiles.h"
#include "globals.h"
#include "utils.h"
#include "logs_app.h"

/* ------------------------------------------------------------------ */
/* Lista todos los perfiles con sus permisos                           */
/* ------------------------------------------------------------------ */
void perfiles_listar(void) {
    const char *sql =
        "SELECT id, nombre,"
        " ver_ultima_medicion, ver_historico, ver_ranking,"
        " ver_por_municipio, ver_por_provincia"
        " FROM PERFILES ORDER BY id;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando perfiles.\n");
        return;
    }

    printf("\n==================== PERFILES ====================\n");
    printf(" %-3s %-14s  UltMed  Hist  Rank  Munic  Prov\n",
           "ID", "Nombre");
    printf("---------------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int  id  = sqlite3_column_int (stmt, 0);
        const char *nm = (const char *)sqlite3_column_text(stmt, 1);
        int um  = sqlite3_column_int(stmt, 2);
        int hi  = sqlite3_column_int(stmt, 3);
        int rk  = sqlite3_column_int(stmt, 4);
        int mu  = sqlite3_column_int(stmt, 5);
        int pr  = sqlite3_column_int(stmt, 6);
        printf(" %-3d %-14s  %-7s %-6s %-6s %-7s %s\n",
               id, nm,
               um ? "SI":"NO", hi ? "SI":"NO",
               rk ? "SI":"NO", mu ? "SI":"NO",
               pr ? "SI":"NO");
        n++;
    }
    if (n == 0) printf("  (no hay perfiles)\n");
    printf("===================================================\n");

    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Crea un nuevo perfil pidiendo nombre y permisos al admin            */
/* ------------------------------------------------------------------ */
int perfiles_crear(void) {
    char nombre[MAX_NOMBRE];
    int um, hi, rk, mu, pr;

    printf("\n--- CREAR PERFIL ---\n");
    printf("Nombre del perfil: ");
    fflush(stdout);
    if (fgets(nombre, sizeof(nombre), stdin) == NULL) return 0;
    nombre[strcspn(nombre, "\r\n")] = '\0';
    if (nombre[0] == '\0') { printf("[AVISO] Nombre vacio.\n"); return 0; }

    printf("Permisos (1=SI, 0=NO):\n");
    printf("  Ver ultima medicion  : "); scanf("%d", &um); limpiarBuffer();
    printf("  Ver historico        : "); scanf("%d", &hi); limpiarBuffer();
    printf("  Ver ranking          : "); scanf("%d", &rk); limpiarBuffer();
    printf("  Ver por municipio    : "); scanf("%d", &mu); limpiarBuffer();
    printf("  Ver por provincia    : "); scanf("%d", &pr); limpiarBuffer();

    const char *sql =
        "INSERT INTO PERFILES"
        " (nombre, ver_ultima_medicion, ver_historico, ver_ranking,"
        "  ver_por_municipio, ver_por_provincia)"
        " VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Preparando sentencia.\n"); return 0;
    }
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int (stmt, 2, um);
    sqlite3_bind_int (stmt, 3, hi);
    sqlite3_bind_int (stmt, 4, rk);
    sqlite3_bind_int (stmt, 5, mu);
    sqlite3_bind_int (stmt, 6, pr);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Perfil '%s' creado correctamente.\n", nombre);
        char acc[MAX_STR];
        snprintf(acc, sizeof(acc), "Perfil creado: %s", nombre);
        log_registrar(g_sesion.usuario.username, acc);
    } else {
        printf("[ERROR] No se pudo crear el perfil (quizas ya existe).\n");
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* Modifica los permisos de un perfil existente                        */
/* ------------------------------------------------------------------ */
int perfiles_modificar(void) {
    perfiles_listar();

    int id;
    printf("\nID del perfil a modificar (0=cancelar): ");
    scanf("%d", &id); limpiarBuffer();
    if (id == 0) return 0;

    /* Verificar que existe */
    Perfil p;
    if (!perfiles_cargar(id, &p)) {
        printf("[ERROR] Perfil no encontrado.\n"); return 0;
    }

    printf("Modificando '%s'. Introduce nuevos permisos (1=SI, 0=NO):\n", p.nombre);
    printf("  Ver ultima medicion  [actual=%d]: ", p.ver_ultima_medicion);
    scanf("%d", &p.ver_ultima_medicion); limpiarBuffer();
    printf("  Ver historico        [actual=%d]: ", p.ver_historico);
    scanf("%d", &p.ver_historico); limpiarBuffer();
    printf("  Ver ranking          [actual=%d]: ", p.ver_ranking);
    scanf("%d", &p.ver_ranking); limpiarBuffer();
    printf("  Ver por municipio    [actual=%d]: ", p.ver_por_municipio);
    scanf("%d", &p.ver_por_municipio); limpiarBuffer();
    printf("  Ver por provincia    [actual=%d]: ", p.ver_por_provincia);
    scanf("%d", &p.ver_por_provincia); limpiarBuffer();

    const char *sql =
        "UPDATE PERFILES SET"
        " ver_ultima_medicion=?, ver_historico=?, ver_ranking=?,"
        " ver_por_municipio=?, ver_por_provincia=?"
        " WHERE id=?;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, p.ver_ultima_medicion);
    sqlite3_bind_int(stmt, 2, p.ver_historico);
    sqlite3_bind_int(stmt, 3, p.ver_ranking);
    sqlite3_bind_int(stmt, 4, p.ver_por_municipio);
    sqlite3_bind_int(stmt, 5, p.ver_por_provincia);
    sqlite3_bind_int(stmt, 6, id);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Permisos del perfil '%s' actualizados.\n", p.nombre);
        char acc[MAX_STR];
        snprintf(acc, sizeof(acc), "Perfil modificado: %s (id=%d)", p.nombre, id);
        log_registrar(g_sesion.usuario.username, acc);
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* Carga un perfil por id en la estructura Perfil                      */
/* ------------------------------------------------------------------ */
int perfiles_cargar(int id_perfil, Perfil *p) {
    const char *sql =
        "SELECT id, nombre, ver_ultima_medicion, ver_historico,"
        " ver_ranking, ver_por_municipio, ver_por_provincia"
        " FROM PERFILES WHERE id=?;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, id_perfil);

    int ok = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        p->id = sqlite3_column_int(stmt, 0);
        strncpy(p->nombre, (const char *)sqlite3_column_text(stmt, 1),
                MAX_NOMBRE - 1);
        p->ver_ultima_medicion = sqlite3_column_int(stmt, 2);
        p->ver_historico       = sqlite3_column_int(stmt, 3);
        p->ver_ranking         = sqlite3_column_int(stmt, 4);
        p->ver_por_municipio   = sqlite3_column_int(stmt, 5);
        p->ver_por_provincia   = sqlite3_column_int(stmt, 6);
        ok = 1;
    }
    sqlite3_finalize(stmt);
    return ok;
}
