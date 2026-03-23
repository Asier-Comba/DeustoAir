#ifndef MEDICIONES_H
#define MEDICIONES_H

/* Consultas de datos para el menu de estadisticas */
void med_ultima_por_estacion(void);
void med_historico_municipio(void);
void med_ranking_contaminante(void);
void med_media_por_provincia(void);
void med_alertas_superacion(void);   /* extra: muestra valores que superan umbrales */

#endif /* MEDICIONES_H */
