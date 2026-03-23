#include <stdio.h>
#include <string.h>
#include "config.h"

/* Lee el fichero de configuracion con formato CLAVE=VALOR */
int cargarConfig(const char *ruta, Config *cfg) {
    /* Valores por defecto */
    strncpy(cfg->db_path,   "data/deustoair.db",          MAX_PATH   - 1);
    strncpy(cfg->log_path,  "data/logs.txt",              MAX_PATH   - 1);
    strncpy(cfg->data_path, "data/datos_calidad_aire.csv",MAX_PATH   - 1);
    strncpy(cfg->admin_user,"admin",                      MAX_NOMBRE - 1);
    strncpy(cfg->admin_pass,"admin123",                   MAX_NOMBRE - 1);

    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("[AVISO] No se encontro '%s'. Usando valores por defecto.\n", ruta);
        return 1;   /* no es error fatal */
    }

    char linea[512];
    while (fgets(linea, sizeof(linea), f)) {
        /* Quitar salto de linea */
        linea[strcspn(linea, "\r\n")] = '\0';
        /* Ignorar comentarios y lineas vacias */
        if (linea[0] == '#' || linea[0] == '\0') continue;

        char *sep = strchr(linea, '=');
        if (!sep) continue;
        *sep = '\0';
        char *clave = linea;
        char *valor = sep + 1;

        if      (strcmp(clave, "DB_PATH")    == 0) strncpy(cfg->db_path,   valor, MAX_PATH   - 1);
        else if (strcmp(clave, "LOG_PATH")   == 0) strncpy(cfg->log_path,  valor, MAX_PATH   - 1);
        else if (strcmp(clave, "DATA_PATH")  == 0) strncpy(cfg->data_path, valor, MAX_PATH   - 1);
        else if (strcmp(clave, "ADMIN_USER") == 0) strncpy(cfg->admin_user,valor, MAX_NOMBRE - 1);
        else if (strcmp(clave, "ADMIN_PASS") == 0) strncpy(cfg->admin_pass,valor, MAX_NOMBRE - 1);
    }

    fclose(f);
    return 1;
}

void mostrarConfig(const Config *cfg) {
    printf("\n--- Configuracion actual ---\n");
    printf("  Base de datos : %s\n", cfg->db_path);
    printf("  Fichero logs  : %s\n", cfg->log_path);
    printf("  Fichero datos : %s\n", cfg->data_path);
    printf("----------------------------\n");
}
