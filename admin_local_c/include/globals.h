#ifndef GLOBALS_H
#define GLOBALS_H

#include "sqlite3.h"
#include "types.h"
#include "config.h"

/* Base de datos SQLite (un unico handle global) */
extern sqlite3 *g_db;

/* Sesion del usuario actual */
extern Sesion g_sesion;

/* Configuracion cargada al inicio */
extern Config g_config;

#endif /* GLOBALS_H */
