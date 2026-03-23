#ifndef MENU_H
#define MENU_H

/* Menu raiz (sin sesion) */
int menu_principal(void);

/* Menus tras login */
void menu_usuario(void);
void menu_admin(void);

/* Submenus del administrador */
void menu_gestion_datos(void);
void menu_gestion_usuarios(void);
void menu_gestion_perfiles(void);
void menu_estadisticas_admin(void);
void menu_sistema(void);

/* Submenu de estadisticas del usuario normal */
void menu_estadisticas_usuario(void);

#endif /* MENU_H */
