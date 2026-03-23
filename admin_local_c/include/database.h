#ifndef DATABASE_H
#define DATABASE_H

int  db_init(const char *ruta);
void db_insertar_datos_iniciales(void);
void db_close(void);
int  db_borrar_datos(void);          /* borra mediciones y estaciones */

/* Helpers para obtener fecha/hora actual como cadena */
void db_fecha_hora_actual(char *buf, int tam);

#endif /* DATABASE_H */
