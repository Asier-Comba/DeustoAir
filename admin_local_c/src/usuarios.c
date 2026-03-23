#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include "perfiles.h"
#include "globals.h"
#include "utils.h"
#include "logs_app.h"

/* ------------------------------------------------------------------ */
/* Lista todos los usuarios con su perfil y estado                     */
/* ------------------------------------------------------------------ */
void usuarios_listar(void) {
    const char *sql =
        "SELECT u.id, u.username, u.email,"
        " COALESCE(p.nombre,'(admin)') AS perfil,"
        " u.activo, u.es_admin"
        " FROM USUARIOS u"
        " LEFT JOIN PERFILES p ON u.id_perfil = p.id"
        " ORDER BY u.id;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("[ERROR] Consultando usuarios.\n"); return;
    }

    printf("\n=================== USUARIOS ===================\n");
    printf(" %-3s %-15s %-25s %-12s %-6s %s\n",
           "ID","Usuario","Email","Perfil","Activo","Admin");
    printf("-------------------------------------------------\n");

    int n = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf(" %-3d %-15s %-25s %-12s %-6s %s\n",
               sqlite3_column_int (stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_int (stmt, 4) ? "SI":"NO",
               sqlite3_column_int (stmt, 5) ? "SI":"NO");
        n++;
    }
    if (n == 0) printf("  (no hay usuarios)\n");
    printf("=================================================\n");
    sqlite3_finalize(stmt);
}

/* ------------------------------------------------------------------ */
/* Asigna un perfil a un usuario (admin lo hace por cualquier usuario) */
/* ------------------------------------------------------------------ */
int usuarios_cambiar_perfil(void) {
    usuarios_listar();
    int uid;
    printf("\nID de usuario al que asignar perfil (0=cancelar): ");
    scanf("%d", &uid); limpiarBuffer();
    if (uid == 0) return 0;

    perfiles_listar();
    int pid;
    printf("\nID del perfil a asignar (0=cancelar): ");
    scanf("%d", &pid); limpiarBuffer();
    if (pid == 0) return 0;

    const char *sql = "UPDATE USUARIOS SET id_perfil=? WHERE id=?;";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, pid);
    sqlite3_bind_int(stmt, 2, uid);
    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Perfil actualizado.\n");
        char acc[MAX_STR];
        snprintf(acc, sizeof(acc), "Perfil cambiado: usuario_id=%d -> perfil_id=%d", uid, pid);
        log_registrar(g_sesion.usuario.username, acc);
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* Activa o desactiva un usuario                                       */
/* ------------------------------------------------------------------ */
int usuarios_toggle_activo(void) {
    usuarios_listar();
    int uid;
    printf("\nID de usuario a activar/desactivar (0=cancelar): ");
    scanf("%d", &uid); limpiarBuffer();
    if (uid == 0) return 0;

    const char *sql =
        "UPDATE USUARIOS SET activo = CASE WHEN activo=1 THEN 0 ELSE 1 END WHERE id=?;";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, uid);
    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Estado del usuario actualizado.\n");
        char acc[MAX_STR];
        snprintf(acc, sizeof(acc), "Estado usuario cambiado: id=%d", uid);
        log_registrar(g_sesion.usuario.username, acc);
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* Cambia la contrasena del usuario indicado                           */
/* ------------------------------------------------------------------ */
int usuarios_cambiar_password(const char *username) {
    char nueva[MAX_NOMBRE], confirma[MAX_NOMBRE];

    printf("Nueva contrasena: "); fflush(stdout);
    if (fgets(nueva, sizeof(nueva), stdin) == NULL) return 0;
    nueva[strcspn(nueva, "\r\n")] = '\0';
    if (nueva[0] == '\0') { printf("[AVISO] Contrasena vacia.\n"); return 0; }

    printf("Confirmar contrasena: "); fflush(stdout);
    if (fgets(confirma, sizeof(confirma), stdin) == NULL) return 0;
    confirma[strcspn(confirma, "\r\n")] = '\0';

    if (strcmp(nueva, confirma) != 0) {
        printf("[ERROR] Las contrasenas no coinciden.\n"); return 0;
    }

    const char *sql = "UPDATE USUARIOS SET password=? WHERE username=?;";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, nueva,    -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);
    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Contrasena actualizada.\n");
        char acc[MAX_STR];
        snprintf(acc, sizeof(acc), "Password cambiado: usuario=%s", username);
        log_registrar(g_sesion.usuario.username, acc);
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* Login: busca usuario/pass y carga el perfil con permisos            */
/* ------------------------------------------------------------------ */
int usuarios_login(const char *username, const char *password, Usuario *u) {
    const char *sql =
        "SELECT id, username, password, email, id_perfil, activo, es_admin"
        " FROM USUARIOS WHERE username=? AND password=? AND activo=1;";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    int ok = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        u->id = sqlite3_column_int(stmt, 0);
        strncpy(u->username, (const char *)sqlite3_column_text(stmt, 1), MAX_NOMBRE - 1);
        strncpy(u->password, (const char *)sqlite3_column_text(stmt, 2), MAX_NOMBRE - 1);
        if (sqlite3_column_text(stmt, 3))
            strncpy(u->email, (const char *)sqlite3_column_text(stmt, 3), MAX_STR - 1);
        u->id_perfil = sqlite3_column_int(stmt, 4);
        u->activo    = sqlite3_column_int(stmt, 5);
        u->es_admin  = sqlite3_column_int(stmt, 6);

        /* Cargar permisos del perfil */
        if (!u->es_admin && u->id_perfil > 0) {
            perfiles_cargar(u->id_perfil, &u->perfil);
        } else {
            /* Admin tiene todos los permisos */
            u->perfil.ver_ultima_medicion = 1;
            u->perfil.ver_historico       = 1;
            u->perfil.ver_ranking         = 1;
            u->perfil.ver_por_municipio   = 1;
            u->perfil.ver_por_provincia   = 1;
        }
        ok = 1;
    }
    sqlite3_finalize(stmt);
    return ok;
}

/* ------------------------------------------------------------------ */
/* Registro de nuevo usuario (desde menu principal)                    */
/* ------------------------------------------------------------------ */
int usuarios_registrar(void) {
    char username[MAX_NOMBRE], password[MAX_NOMBRE];
    char confirma[MAX_NOMBRE], email[MAX_STR];

    printf("\n--- REGISTRO DE USUARIO ---\n");
    printf("Usuario  : "); fflush(stdout);
    if (fgets(username, sizeof(username), stdin) == NULL) return 0;
    username[strcspn(username, "\r\n")] = '\0';
    if (username[0] == '\0') { printf("[ERROR] Usuario vacio.\n"); return 0; }

    printf("Email    : "); fflush(stdout);
    if (fgets(email, sizeof(email), stdin) == NULL) return 0;
    email[strcspn(email, "\r\n")] = '\0';

    printf("Password : "); fflush(stdout);
    if (fgets(password, sizeof(password), stdin) == NULL) return 0;
    password[strcspn(password, "\r\n")] = '\0';
    if (password[0] == '\0') { printf("[ERROR] Password vacio.\n"); return 0; }

    printf("Confirmar password: "); fflush(stdout);
    if (fgets(confirma, sizeof(confirma), stdin) == NULL) return 0;
    confirma[strcspn(confirma, "\r\n")] = '\0';

    if (strcmp(password, confirma) != 0) {
        printf("[ERROR] Las contrasenas no coinciden.\n"); return 0;
    }

    /* Asignar perfil 'Estandar' por defecto (id=2) */
    const char *sql =
        "INSERT INTO USUARIOS (username, password, email, id_perfil, activo, es_admin)"
        " VALUES (?, ?, ?, 2, 1, 0);";

    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email,    -1, SQLITE_STATIC);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    if (ok) {
        printf("[OK] Usuario '%s' registrado con perfil 'Estandar'.\n", username);
        log_registrar(username, "Registro de usuario");
    } else {
        printf("[ERROR] No se pudo registrar. El usuario ya puede existir.\n");
    }
    return ok;
}
