#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "import_datos.h"
#include "globals.h"
#include "logs_app.h"

/* ------------------------------------------------------------------ */
/* Devuelve el id de una estacion (la crea si no existe)               */
/* ------------------------------------------------------------------ */
static int obtener_o_crear_estacion(const char *nombre,
                                    const char *municipio,
                                    const char *provincia) {
    /* Buscar existente */
    const char *sql_sel =
        "SELECT id FROM ESTACIONES"
        " WHERE nombre=? AND municipio=? AND provincia=?;";

    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(g_db, sql_sel, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre,    -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, municipio, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, provincia, -1, SQLITE_STATIC);

    int id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (id > 0) return id;

    /* Insertar nueva */
    const char *sql_ins =
        "INSERT INTO ESTACIONES (nombre, municipio, provincia)"
        " VALUES (?, ?, ?);";
    sqlite3_prepare_v2(g_db, sql_ins, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre,    -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, municipio, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, provincia, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(g_db);
}

/* ------------------------------------------------------------------ */
/* Divide una linea CSV por el separador ';'                           */
/* ------------------------------------------------------------------ */
static int split_csv(char *linea, char *campos[], int max_campos) {
    int n = 0;
    char *p = linea;
    while (*p && n < max_campos) {
        campos[n++] = p;
        char *sep = strchr(p, ';');
        if (!sep) break;
        *sep = '\0';
        p = sep + 1;
    }
    return n;
}

/* ------------------------------------------------------------------ */
/* Importa el fichero CSV; devuelve numero de filas insertadas         */
/* Formato: FECHA;ESTACION;MUNICIPIO;PROVINCIA;SO2;NO2;PM10            */
/* ------------------------------------------------------------------ */
int import_csv(const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("[ERROR] No se pudo abrir '%s'\n", ruta);
        return 0;
    }

    /* Activar transaccion para mayor velocidad */
    sqlite3_exec(g_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    const char *sql_ins =
        "INSERT INTO MEDICIONES (id_estacion, fecha, so2, no2, pm10)"
        " VALUES (?, ?, ?, ?, ?);";

    char linea[1024];
    int  fila   = 0;
    int  ok     = 0;
    int  errores = 0;

    while (fgets(linea, sizeof(linea), f)) {
        fila++;
        linea[strcspn(linea, "\r\n")] = '\0';
        if (fila == 1) continue;        /* saltar cabecera */
        if (linea[0] == '\0') continue; /* saltar vacias   */

        char *campos[8];
        int  nc = split_csv(linea, campos, 8);
        if (nc < 7) { errores++; continue; }

        /* FECHA;ESTACION;MUNICIPIO;PROVINCIA;SO2;NO2;PM10 */
        char *fecha     = campos[0];
        char *estacion  = campos[1];
        char *municipio = campos[2];
        char *provincia = campos[3];
        double so2  = atof(campos[4]);
        double no2  = atof(campos[5]);
        double pm10 = atof(campos[6]);

        int id_est = obtener_o_crear_estacion(estacion, municipio, provincia);
        if (id_est <= 0) { errores++; continue; }

        sqlite3_stmt *stmt = NULL;
        sqlite3_prepare_v2(g_db, sql_ins, -1, &stmt, NULL);
        sqlite3_bind_int   (stmt, 1, id_est);
        sqlite3_bind_text  (stmt, 2, fecha,  -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 3, so2);
        sqlite3_bind_double(stmt, 4, no2);
        sqlite3_bind_double(stmt, 5, pm10);

        if (sqlite3_step(stmt) == SQLITE_DONE) ok++;
        else errores++;
        sqlite3_finalize(stmt);
    }

    sqlite3_exec(g_db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);

    printf("[OK] Importacion completada: %d filas insertadas, %d errores.\n",
           ok, errores);

    char acc[MAX_STR];
    snprintf(acc, sizeof(acc), "Importacion CSV: %d filas ok, fichero=%s", ok, ruta);
    log_registrar(g_sesion.usuario.username, acc);

    return ok;
}

/* ------------------------------------------------------------------ */
/* Lista las estaciones registradas en la BD                           */
/* ------------------------------------------------------------------ */
void import_ver_estaciones(void) {
    const char *sql =
        "SELECT e.id, e.nombre, e.municipio, e.provincia,"
        " COUNT(m.id) as n_meds"
        " FROM ESTACIONES e"
        " LEFT JOIN MEDICIONES m ON m.id_estacion = e.id"
        " GROUP BY e.id"
        " ORDER BY e.provincia, e.municipio;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando estaciones.\n"); return;
    }

    printf("\n====== ESTACIONES REGISTRADAS ======\n");
    printf("%-4s %-30s %-15s %-10s  Meds\n",
           "ID","Nombre","Municipio","Provincia");
    printf("------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-4d %-30s %-15s %-10s  %4d\n",
               sqlite3_column_int (stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_int (stmt, 4));
        n++;
    }
    if (n == 0) printf("  (no hay estaciones)\n");
    printf("====================================\n");
    sqlite3_finalize(stmt);
}
