#include <stdio.h>
#include <string.h>
#include "mediciones.h"
#include "globals.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
/* Muestra la ultima medicion de cada estacion                         */
/* ------------------------------------------------------------------ */
void med_ultima_por_estacion(void) {
    const char *sql =
        "SELECT e.nombre, e.municipio, e.provincia,"
        " m.fecha, m.so2, m.no2, m.pm10"
        " FROM MEDICIONES m"
        " JOIN ESTACIONES e ON m.id_estacion = e.id"
        " WHERE m.id IN ("
        "   SELECT MAX(id) FROM MEDICIONES GROUP BY id_estacion"
        " )"
        " ORDER BY e.provincia, e.municipio;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando mediciones.\n"); return;
    }

    printf("\n====== ULTIMA MEDICION POR ESTACION ======\n");
    printf("%-30s %-15s %-10s  SO2   NO2  PM10\n",
           "Estacion","Municipio","Fecha");
    printf("------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-30s %-15s %-10s %5.1f %5.1f %5.1f\n",
               sqlite3_column_text(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_double(stmt, 4),
               sqlite3_column_double(stmt, 5),
               sqlite3_column_double(stmt, 6));
        n++;
    }
    if (n == 0) printf("  (no hay datos importados)\n");
    printf("==========================================\n");
    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Muestra historico de mediciones de un municipio concreto            */
/* ------------------------------------------------------------------ */
void med_historico_municipio(void) {
    char muni[MAX_NOMBRE];
    printf("Municipio a consultar: "); fflush(stdout);
    if (fgets(muni, sizeof(muni), stdin) == NULL) return;
    muni[strcspn(muni, "\r\n")] = '\0';
    if (muni[0] == '\0') return;

    const char *sql =
        "SELECT e.nombre, m.fecha, m.so2, m.no2, m.pm10"
        " FROM MEDICIONES m"
        " JOIN ESTACIONES e ON m.id_estacion = e.id"
        " WHERE LOWER(e.municipio) = LOWER(?)"
        " ORDER BY m.fecha DESC LIMIT 50;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando historico.\n"); return;
    }
    sqlite3_bind_text(stmt, 1, muni, -1, SQLITE_STATIC);

    printf("\n====== HISTORICO: %s ======\n", muni);
    printf("%-30s %-12s  SO2   NO2  PM10\n", "Estacion","Fecha");
    printf("-------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-30s %-12s %5.1f %5.1f %5.1f\n",
               sqlite3_column_text(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_double(stmt, 2),
               sqlite3_column_double(stmt, 3),
               sqlite3_column_double(stmt, 4));
        n++;
    }
    if (n == 0) printf("  (sin datos para '%s')\n", muni);
    printf("===========================================\n");
    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Ranking de estaciones por contaminante (media del periodo)          */
/* ------------------------------------------------------------------ */
void med_ranking_contaminante(void) {
    printf("\nContaminante a ordenar:\n");
    printf("  1) SO2   2) NO2   3) PM10\n");
    printf("Opcion: ");
    int op; scanf("%d", &op); limpiarBuffer();

    const char *col = NULL;
    const char *nombre_col = NULL;
    if      (op == 1) { col = "so2";  nombre_col = "SO2";  }
    else if (op == 2) { col = "no2";  nombre_col = "NO2";  }
    else if (op == 3) { col = "pm10"; nombre_col = "PM10"; }
    else { printf("[ERROR] Opcion no valida.\n"); return; }

    char sql[512];
    snprintf(sql, sizeof(sql),
        "SELECT e.nombre, e.municipio, e.provincia,"
        " ROUND(AVG(m.%s), 2) AS media"
        " FROM MEDICIONES m"
        " JOIN ESTACIONES e ON m.id_estacion = e.id"
        " GROUP BY m.id_estacion"
        " ORDER BY media DESC;", col);

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Ejecutando consulta.\n"); return;
    }

    printf("\n====== RANKING POR %s (media) ======\n", nombre_col);
    printf("%-4s %-30s %-15s %-10s  Media\n","Pos","Estacion","Municipio","Provincia");
    printf("---------------------------------------------\n");

    int n = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf(" %-3d %-30s %-15s %-10s %6.2f\n",
               n++,
               sqlite3_column_text  (stmt, 0),
               sqlite3_column_text  (stmt, 1),
               sqlite3_column_text  (stmt, 2),
               sqlite3_column_double(stmt, 3));
    }
    if (n == 1) printf("  (no hay datos)\n");
    printf("=============================================\n");
    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Media de contaminantes agrupada por provincia                       */
/* ------------------------------------------------------------------ */
void med_media_por_provincia(void) {
    const char *sql =
        "SELECT e.provincia,"
        " ROUND(AVG(m.so2),2),"
        " ROUND(AVG(m.no2),2),"
        " ROUND(AVG(m.pm10),2),"
        " COUNT(*) as n_meds"
        " FROM MEDICIONES m"
        " JOIN ESTACIONES e ON m.id_estacion = e.id"
        " GROUP BY e.provincia"
        " ORDER BY e.provincia;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando medias.\n"); return;
    }

    printf("\n====== MEDIA POR PROVINCIA ======\n");
    printf("%-15s  SO2    NO2   PM10   Meds\n","Provincia");
    printf("---------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-15s %5.2f  %5.2f  %5.2f  %4d\n",
               sqlite3_column_text  (stmt, 0),
               sqlite3_column_double(stmt, 1),
               sqlite3_column_double(stmt, 2),
               sqlite3_column_double(stmt, 3),
               sqlite3_column_int   (stmt, 4));
        n++;
    }
    if (n == 0) printf("  (no hay datos)\n");
    printf("=================================\n");
    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Alertas: mediciones que superan los umbrales de la OMS              */
/* SO2>40, NO2>40, PM10>20 (valores anuales orientativos)              */
/* ------------------------------------------------------------------ */
void med_alertas_superacion(void) {
    const char *sql =
        "SELECT e.nombre, e.municipio, m.fecha,"
        " m.so2, m.no2, m.pm10"
        " FROM MEDICIONES m"
        " JOIN ESTACIONES e ON m.id_estacion = e.id"
        " WHERE m.so2 > 40 OR m.no2 > 40 OR m.pm10 > 20"
        " ORDER BY m.fecha DESC;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando alertas.\n"); return;
    }

    printf("\n====== ALERTAS: VALORES SOBRE UMBRAL ======\n");
    printf("[Umbrales: SO2>40, NO2>40, PM10>20]\n");
    printf("%-28s %-13s %-12s  SO2   NO2  PM10\n",
           "Estacion","Municipio","Fecha");
    printf("-------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-28s %-13s %-12s %5.1f %5.1f %5.1f\n",
               sqlite3_column_text  (stmt, 0),
               sqlite3_column_text  (stmt, 1),
               sqlite3_column_text  (stmt, 2),
               sqlite3_column_double(stmt, 3),
               sqlite3_column_double(stmt, 4),
               sqlite3_column_double(stmt, 5));
        n++;
    }
    if (n == 0) printf("  (ninguna medicion supera los umbrales)\n");
    printf("===========================================\n");
    sqlite3_finalize(stmt);
}
