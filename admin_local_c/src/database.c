#include <stdio.h>
#include <string.h>
#include <time.h>
#include "database.h"
#include "globals.h"

/* Definicion de los globales (solo aqui, el resto los usa via extern) */
sqlite3 *g_db      = NULL;
Sesion   g_sesion  = {0};
Config   g_config;


int db_init(const char *ruta) {
    int rc = sqlite3_open(ruta, &g_db);
    if (rc != SQLITE_OK) {
        printf("[ERROR] No se pudo abrir la base de datos: %s\n",
               sqlite3_errmsg(g_db));
        return 0;
    }

    /* Activar claves foraneas */
    sqlite3_exec(g_db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    /* SQL de creacion de tablas */
    const char *sql =
        /* 1. Perfiles con flags de permisos */
        "CREATE TABLE IF NOT EXISTS PERFILES ("
        "  id                   INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  nombre               TEXT    NOT NULL UNIQUE,"
        "  ver_ultima_medicion  INTEGER NOT NULL DEFAULT 1,"
        "  ver_historico        INTEGER NOT NULL DEFAULT 1,"
        "  ver_ranking          INTEGER NOT NULL DEFAULT 0,"
        "  ver_por_municipio    INTEGER NOT NULL DEFAULT 1,"
        "  ver_por_provincia    INTEGER NOT NULL DEFAULT 0"
        ");"

        /* 2. Usuarios */
        "CREATE TABLE IF NOT EXISTS USUARIOS ("
        "  id        INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  username  TEXT    NOT NULL UNIQUE,"
        "  password  TEXT    NOT NULL,"
        "  email     TEXT,"
        "  id_perfil INTEGER REFERENCES PERFILES(id),"
        "  activo    INTEGER NOT NULL DEFAULT 1,"
        "  es_admin  INTEGER NOT NULL DEFAULT 0"
        ");"

        /* 3. Estaciones de medicion */
        "CREATE TABLE IF NOT EXISTS ESTACIONES ("
        "  id        INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  nombre    TEXT    NOT NULL,"
        "  municipio TEXT    NOT NULL,"
        "  provincia TEXT    NOT NULL"
        ");"

        /* 4. Mediciones de calidad del aire */
        "CREATE TABLE IF NOT EXISTS MEDICIONES ("
        "  id          INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  id_estacion INTEGER NOT NULL REFERENCES ESTACIONES(id),"
        "  fecha       TEXT    NOT NULL,"
        "  so2         REAL    NOT NULL DEFAULT 0,"
        "  no2         REAL    NOT NULL DEFAULT 0,"
        "  pm10        REAL    NOT NULL DEFAULT 0"
        ");"

        /* 5. Registro de operaciones */
        "CREATE TABLE IF NOT EXISTS LOGS ("
        "  id         INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  fecha_hora TEXT    NOT NULL,"
        "  usuario    TEXT    NOT NULL,"
        "  accion     TEXT    NOT NULL"
        ");";

    char *err = NULL;
    rc = sqlite3_exec(g_db, sql, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        printf("[ERROR] Creando tablas: %s\n", err);
        sqlite3_free(err);
        return 0;
    }

    db_insertar_datos_iniciales();
    printf("[OK] Base de datos lista: %s\n", ruta);
    return 1;
}

/* ------------------------------------------------------------------ */
/* Inserta perfiles y admin por defecto (solo si no existen)           */
/* ------------------------------------------------------------------ */
void db_insertar_datos_iniciales(void) {
    const char *sql =
        /* Tres perfiles de ejemplo con distintos niveles de acceso */
        "INSERT OR IGNORE INTO PERFILES"
        " (nombre, ver_ultima_medicion, ver_historico, ver_ranking, ver_por_municipio, ver_por_provincia)"
        " VALUES"
        " ('Basico',    1, 0, 0, 0, 0),"
        " ('Estandar',  1, 1, 0, 1, 0),"
        " ('Avanzado',  1, 1, 1, 1, 1);"

        /* Usuario administrador por defecto */
        "INSERT OR IGNORE INTO USUARIOS"
        " (username, password, email, id_perfil, activo, es_admin)"
        " VALUES ('admin', 'admin123', 'admin@deustoair.com', NULL, 1, 1);";

    sqlite3_exec(g_db, sql, NULL, NULL, NULL);
}

/* ------------------------------------------------------------------ */
/* Borra mediciones y estaciones (reset de datos importados)           */
/* ------------------------------------------------------------------ */
int db_borrar_datos(void) {
    const char *sql =
        "DELETE FROM MEDICIONES;"
        "DELETE FROM ESTACIONES;"
        "DELETE FROM sqlite_sequence WHERE name='MEDICIONES';"
        "DELETE FROM sqlite_sequence WHERE name='ESTACIONES';";

    char *err = NULL;
    int rc = sqlite3_exec(g_db, sql, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        printf("[ERROR] Borrando datos: %s\n", err);
        sqlite3_free(err);
        return 0;
    }
    return 1;
}

/* ------------------------------------------------------------------ */
/* Devuelve la fecha/hora actual como "YYYY-MM-DD HH:MM:SS"            */
/* ------------------------------------------------------------------ */
void db_fecha_hora_actual(char *buf, int tam) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, tam, "%Y-%m-%d %H:%M:%S", tm_info);
}

void db_close(void) {
    if (g_db) {
        sqlite3_close(g_db);
        g_db = NULL;
    }
}
