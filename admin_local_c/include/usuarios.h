#ifndef USUARIOS_H
#define USUARIOS_H

#include "types.h"

void usuarios_listar(void);
int  usuarios_cambiar_perfil(void);
int  usuarios_toggle_activo(void);
int  usuarios_cambiar_password(const char *username);

/* Busca un usuario por username+password; devuelve 1 si ok */
int  usuarios_login(const char *username, const char *password, Usuario *u);

/* Registra un nuevo usuario (sin privilegios de admin) */
int  usuarios_registrar(void);

#endif /* USUARIOS_H */
