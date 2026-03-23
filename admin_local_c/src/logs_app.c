#include <stdio.h>
#include <string.h>
#include "logs_app.h"
#include "database.h"
#include "globals.h"

/* ------------------------------------------------------------------ */
/* Registra una accion en la tabla LOGS y en el fichero de texto       */
/* ------------------------------------------------------------------ */
void log_registrar(const char *usuario, const char *accion) {
    char fecha_hora[MAX_FECHA];
    db_fecha_hora_actual(fecha_hora, sizeof(fecha_hora));

    /* 1) Escribir en la BD */
    if (g_db) {
        const char *sql =
            "INSERT INTO LOGS (fecha_hora, usuario, accion) VALUES (?, ?, ?);";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, fecha_hora, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, usuario,    -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, accion,     -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }

    /* 2) Escribir en el fichero de texto (modo append) */
    FILE *f = fopen(g_config.log_path, "a");
    if (f) {
        fprintf(f, "[%s] - %s - %s\n", fecha_hora, usuario, accion);
        fclose(f);
    }
}

/* ------------------------------------------------------------------ */
/* Muestra los ultimos 20 registros del log en pantalla                */
/* ------------------------------------------------------------------ */
void log_mostrar(void) {
    const char *sql =
        "SELECT fecha_hora, usuario, accion FROM LOGS"
        " ORDER BY id DESC LIMIT 20;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando logs.\n");
        return;
    }

    printf("\n========== REGISTRO DE LOGS (ultimos 20) ==========\n");
    printf("%-22s %-15s %s\n", "Fecha/Hora", "Usuario", "Accion");
    printf("----------------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *fh  = (const char *)sqlite3_column_text(stmt, 0);
        const char *usr = (const char *)sqlite3_column_text(stmt, 1);
        const char *acc = (const char *)sqlite3_column_text(stmt, 2);
        printf("%-22s %-15s %s\n", fh, usr, acc);
        n++;
    }
    if (n == 0) printf("  (no hay registros)\n");
    printf("====================================================\n");

    sqlite3_finalize(stmt);
}
