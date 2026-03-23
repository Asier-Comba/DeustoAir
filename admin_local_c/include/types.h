#ifndef TYPES_H
#define TYPES_H

#define MAX_STR    256
#define MAX_NOMBRE 128
#define MAX_FECHA   32
#define MAX_PATH   256

/* ─── Perfil de usuario con permisos ─────────────────────────── */
typedef struct {
    int  id;
    char nombre[MAX_NOMBRE];
    int  ver_ultima_medicion;
    int  ver_historico;
    int  ver_ranking;
    int  ver_por_municipio;
    int  ver_por_provincia;
} Perfil;

/* ─── Usuario del sistema ─────────────────────────────────────── */
typedef struct {
    int  id;
    char username[MAX_NOMBRE];
    char password[MAX_NOMBRE];
    char email[MAX_STR];
    int  id_perfil;
    int  activo;
    int  es_admin;
    Perfil perfil;           /* permisos heredados del perfil */
} Usuario;

/* ─── Estacion de medicion ────────────────────────────────────── */
typedef struct {
    int  id;
    char nombre[MAX_STR];
    char municipio[MAX_NOMBRE];
    char provincia[MAX_NOMBRE];
} Estacion;

/* ─── Medicion de calidad del aire ───────────────────────────── */
typedef struct {
    int    id;
    int    id_estacion;
    char   nombre_estacion[MAX_STR];
    char   municipio[MAX_NOMBRE];
    char   provincia[MAX_NOMBRE];
    char   fecha[MAX_FECHA];
    double so2;
    double no2;
    double pm10;
} Medicion;

/* ─── Sesion activa ──────────────────────────────────────────── */
typedef struct {
    int     activo;
    Usuario usuario;
} Sesion;

#endif /* TYPES_H */
