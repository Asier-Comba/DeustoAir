#ifndef IMPORT_DATOS_H
#define IMPORT_DATOS_H

/* Importa el CSV indicado en la configuracion; devuelve nº de filas ok */
int import_csv(const char *ruta);

/* Muestra lista de estaciones cargadas */
void import_ver_estaciones(void);

#endif /* IMPORT_DATOS_H */
