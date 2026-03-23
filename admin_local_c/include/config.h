#ifndef CONFIG_H
#define CONFIG_H

#include "types.h"

typedef struct {
    char db_path[MAX_PATH];
    char log_path[MAX_PATH];
    char data_path[MAX_PATH];
    char admin_user[MAX_NOMBRE];
    char admin_pass[MAX_NOMBRE];
} Config;

int  cargarConfig(const char *ruta, Config *cfg);
void mostrarConfig(const Config *cfg);

#endif /* CONFIG_H */
