<div align="center">

# 🌍 DeustoAir

### *Sistema de gestión y consulta de datos de calidad del aire*  
**Proyecto de Programación IV**

<p>
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="C">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C.svg" alt="C++">
  <img src="https://img.shields.io/badge/Database-SQLite-003B57.svg" alt="SQLite">
  <img src="https://img.shields.io/badge/IDE-Eclipse-2C2255.svg" alt="Eclipse">
  <img src="https://img.shields.io/badge/Status-In%20Development-orange.svg" alt="Status">
</p>

<p>
  Aplicación cliente-servidor orientada a la <b>administración</b>, <b>consulta</b> y <b>análisis</b> de datos de calidad del aire.
</p>

</div>

---

## 📌 Descripción

**DeustoAir** es un proyecto académico desarrollado en el contexto de la asignatura **Programación IV**.  
El objetivo es construir una aplicación modular basada en una arquitectura **cliente-servidor**, capaz de gestionar usuarios, consultar mediciones de calidad del aire y ofrecer estadísticas a partir de datos almacenados en una base de datos.

El sistema se divide en tres grandes bloques:

- **Administrador local (C):** gestión de usuarios, permisos y funciones administrativas.
- **Servidor remoto (C):** procesamiento de peticiones, acceso a base de datos y gestión de sockets.
- **Cliente remoto (C++):** consulta de datos y estadísticas por parte del usuario final.

---

## 🎯 Objetivos del proyecto

- Implementar una aplicación modular en **C y C++**.
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
                            | TCP/IP
                            |
                            +------------> Servidor remoto
