<div align="center">

# 🌍 DeustoAir

### Sistema de gestión y consulta de datos de calidad del aire  
**Proyecto de Programación IV**

<p>
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/C%2B%2B-004482?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/SQLite-07405E?style=for-the-badge&logo=sqlite&logoColor=white" alt="SQLite">
  <img src="https://img.shields.io/badge/Eclipse-2C2255?style=for-the-badge&logo=eclipseide&logoColor=white" alt="Eclipse">
  <img src="https://img.shields.io/badge/Estado-En%20desarrollo-orange?style=for-the-badge" alt="Estado">
</p>

<p>
  Aplicación <b>cliente-servidor</b> orientada a la <b>administración</b>, <b>consulta</b> y <b>análisis</b> de datos de calidad del aire.
</p>

</div>

---

## 📌 Descripción

**DeustoAir** es un proyecto académico desarrollado en el contexto de la asignatura **Programación IV**.

El objetivo es construir una aplicación modular basada en una arquitectura **cliente-servidor**, capaz de gestionar usuarios, consultar mediciones de calidad del aire y ofrecer estadísticas a partir de datos almacenados en una base de datos.

### 🏗️ Componentes del sistema

- **Administrador local (C):** gestión de usuarios, permisos y funciones administrativas.
- **Servidor remoto (C):** procesamiento de peticiones, acceso a base de datos y gestión de sockets.
- **Cliente remoto (C++):** consulta de datos y estadísticas por parte del usuario final.

---

## 🎯 Objetivos del proyecto

- Implementar una aplicación **modular** en C y C++.
- Gestionar **usuarios, roles y permisos**.
- Consultar **mediciones de calidad del aire**.
- Obtener **históricos y estadísticas avanzadas**.
- Utilizar **SQLite** como sistema de persistencia.
- Implementar comunicación mediante **sockets TCP/IP**.
- Seguir una arquitectura realista separando cliente, servidor y administración local.

---

## 🧱 Arquitectura general

```text
                 +----------------------+
                 |   Administrador      |
                 |    local (C)         |
                 +----------+-----------+
                            |
                            | acceso local / configuración
                            |
                 +----------v-----------+
                 |   Servidor remoto    |
                 |      sockets (C)     |
                 +----------+-----------+
                            |
                            | SQLite
                            |
                 +----------v-----------+
                 |    Base de datos     |
                 |       SQLite         |
                 +----------------------+

                 +----------------------+
                 |   Cliente remoto     |
                 |       (C++)          |
                 +----------+-----------+
                            |

⚙️ Tecnologías utilizadas
| Tecnología         | Uso principal                          |
| ------------------ | -------------------------------------- |
| **C**              | Administrador local y servidor remoto  |
| **C++**            | Cliente remoto                         |
| **SQLite**         | Persistencia de datos y almacenamiento |
| **TCP/IP Sockets** | Comunicación cliente-servidor          |
| **Eclipse IDE**    | Entorno de desarrollo                  |



🚧 Estado actual del proyecto

Actualmente se está desarrollando la base del módulo admin_local_c, incluyendo:

estructura inicial del proyecto,

organización modular del código,

menú principal por consola,

preparación para registro e inicio de sesión,

configuración del entorno de compilación en Eclipse.
                            | TCP/IP
                            |
                            +------------> Servidor remoto



🛣️ Roadmap
Fase 1 — Administración local y servidor base

 Crear repositorio y estructura inicial

 Configurar proyecto en Eclipse

 Implementar menú principal inicial

 Implementar registro de usuarios

 Implementar inicio de sesión

 Crear menú de gestión

 Preparar integración con SQLite

 Añadir gestión de usuarios y permisos

Fase 2 — Cliente remoto y estadísticas

 Implementar cliente remoto en C++

 Añadir consultas por estación y municipio

 Implementar rankings y estadísticas avanzadas

 Comparativas entre municipios o regiones

 Validación de permisos desde servidor

👤 Funcionalidades previstas
Administración local

Registro de usuarios

Inicio de sesión

Gestión de usuarios

Gestión de roles y permisos

Importación de datos

Borrado o reinicialización de base de datos

Cliente remoto

Consulta de última medición por estación

Consulta de histórico por municipio

Estadísticas por contaminante

Rankings y comparativas

Visualización según nivel de permisos

▶️ Compilación y ejecución

Actualmente el módulo admin_local_c se compila desde Eclipse con MinGW GCC.

Pasos generales

Abrir el proyecto en Eclipse.

Compilar usando la configuración Debug.

Ejecutar la aplicación desde Eclipse.

Más adelante se añadirán instrucciones detalladas para compilar todos los módulos del sistema.

📚 Contexto académico

Este proyecto ha sido desarrollado como parte de la asignatura Programación IV, siguiendo una metodología por fases en la que se construye progresivamente una solución cliente-servidor completa.

El desarrollo incluye modularidad, separación por componentes y una organización escalable orientada a la implementación progresiva del sistema.

📝 Estado del repositorio

⚠️ Este repositorio se encuentra en desarrollo activo.
La estructura, los módulos y las funcionalidades pueden evolucionar a medida que avance el proyecto.
