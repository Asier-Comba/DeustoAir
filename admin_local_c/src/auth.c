#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "usuarios.h"
#include "globals.h"
#include "utils.h"
#include "logs_app.h"

void auth_iniciar_sesion(void) {
    char username[MAX_NOMBRE];
    char password[MAX_NOMBRE];

    printf("\n==============================\n");
    printf("     INICIAR SESION\n");
    printf("==============================\n");
    printf("Usuario  : "); fflush(stdout);
    if (fgets(username, sizeof(username), stdin) == NULL) return;
    username[strcspn(username, "\r\n")] = '\0';

    printf("Password : "); fflush(stdout);
    if (fgets(password, sizeof(password), stdin) == NULL) return;
    password[strcspn(password, "\r\n")] = '\0';

    Usuario u;
    memset(&u, 0, sizeof(u));

    if (usuarios_login(username, password, &u)) {
        g_sesion.activo  = 1;
        g_sesion.usuario = u;
        printf("\n[OK] Bienvenido, %s! Rol: %s\n",
               u.username, u.es_admin ? "ADMINISTRADOR" : "USUARIO");
        log_registrar(u.username, "Inicio de sesion correcto");
    } else {
        printf("\n[ERROR] Usuario o contrasena incorrectos.\n");
        log_registrar(username, "Intento de login fallido");
    }
}

void auth_registrar_usuario(void) {
    printf("\n==============================\n");
    printf("   REGISTRO DE USUARIO\n");
    printf("==============================\n");
    usuarios_registrar();
}
