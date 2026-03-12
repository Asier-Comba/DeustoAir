<div align="center">

# 🌫️ DeustoAir

### Sistema de gestión y consulta de datos de calidad del aire
**Proyecto de Programación IV — Universidad de Deusto**

<p>
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/C%2B%2B-004482?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/SQLite-07405E?style=for-the-badge&logo=sqlite&logoColor=white" alt="SQLite">
  <img src="https://img.shields.io/badge/Eclipse-2C2255?style=for-the-badge&logo=eclipseide&logoColor=white" alt="Eclipse">
  <img src="https://img.shields.io/badge/Estado-En%20desarrollo-orange?style=for-the-badge" alt="Estado">
</p>

Aplicación **cliente-servidor** orientada a la **administración**, **consulta** y **análisis** de datos de calidad del aire en tiempo real.

</div>

---

## 📌 Descripción

**DeustoAir** es un sistema modular basado en arquitectura **cliente-servidor** capaz de gestionar usuarios, consultar mediciones de calidad del aire y generar estadísticas a partir de una base de datos persistente.

### 🏗️ Componentes del sistema

| Módulo | Lenguaje | Rol |
|---|---|---|
| **Administrador local** | C | Gestión de usuarios, permisos y configuración |
| **Servidor remoto** | C | Procesamiento de peticiones, sockets y acceso a BD |
| **Cliente remoto** | C++ | Consulta de datos y estadísticas por el usuario final |

---

## 🧱 Arquitectura

```
┌─────────────────────┐
│  Administrador      │
│  local (C)          │
└────────┬────────────┘
         │ acceso local
         ▼
┌─────────────────────┐        ┌─────────────────────┐
│  Servidor remoto    │◄──────►│  Cliente remoto     │
│  sockets TCP/IP (C) │        │  (C++)              │
└────────┬────────────┘        └─────────────────────┘
         │ SQLite
         ▼
┌─────────────────────┐
│  Base de datos      │
│  SQLite             │
└─────────────────────┘
```

---

## ⚙️ Tecnologías

| Tecnología | Uso |
|---|---|
| **C** | Administrador local y servidor remoto |
| **C++** | Cliente remoto |
| **SQLite** | Persistencia y almacenamiento de datos |
| **TCP/IP Sockets** | Comunicación cliente-servidor |
| **Eclipse IDE** | Entorno de desarrollo |

---

## 👤 Funcionalidades

### Administración local
- Registro e inicio de sesión de usuarios
- Gestión de roles y permisos
- Importación de datos de mediciones
- Reinicialización de base de datos

### Cliente remoto
- Consulta de última medición por estación
- Histórico por municipio
- Estadísticas por contaminante
- Rankings y comparativas entre municipios
- Visualización según nivel de permisos

---

## 🛣️ Roadmap

**Fase 1 — Administración local y servidor base**
- [x] Crear repositorio y estructura inicial
- [x] Configurar proyecto en Eclipse
- [x] Implementar menú principal
- [ ] Registro e inicio de sesión
- [ ] Gestión de usuarios y permisos
- [ ] Integración con SQLite

**Fase 2 — Cliente remoto y estadísticas**
- [ ] Implementar cliente remoto en C++
- [ ] Consultas por estación y municipio
- [ ] Rankings y estadísticas avanzadas
- [ ] Validación de permisos desde servidor

---

## ▶️ Compilación y ejecución

El módulo `admin_local_c` se compila desde Eclipse con MinGW GCC:

1. Abrir el proyecto en Eclipse
2. Compilar con la configuración `Debug`
3. Ejecutar desde Eclipse

> Se añadirán instrucciones para compilar todos los módulos a medida que avance el proyecto.

---

## 📚 Contexto académico

Proyecto desarrollado en la asignatura **Programación IV**, construido progresivamente siguiendo una metodología por fases. El objetivo es implementar una solución cliente-servidor completa con modularidad, separación de componentes y arquitectura escalable.

---

> ⚠️ Repositorio en desarrollo activo. La estructura y funcionalidades evolucionarán a lo largo del proyecto.
