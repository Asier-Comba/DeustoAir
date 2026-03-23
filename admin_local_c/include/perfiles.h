#ifndef PERFILES_H
#define PERFILES_H

#include "types.h"

void perfiles_listar(void);
int  perfiles_crear(void);
int  perfiles_modificar(void);
int  perfiles_cargar(int id_perfil, Perfil *p);

#endif /* PERFILES_H */
