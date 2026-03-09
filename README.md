<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>DeustoAir - Sistema de Gestión de Calidad del Aire</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px 0;
        }
        
        .container {
            max-width: 900px;
            margin: 0 auto;
            background: white;
            border-radius: 15px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.2);
            overflow: hidden;
        }
        
        /* Header */
        .header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 60px 30px;
            text-align: center;
        }
        
        .header h1 {
            font-size: 3.5em;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.2);
        }
        
        .header .subtitle {
            font-size: 1.3em;
            font-weight: 300;
            margin-bottom: 20px;
            opacity: 0.95;
        }
        
        .header .project-info {
            font-size: 1.1em;
            opacity: 0.9;
            margin-bottom: 25px;
        }
        
        /* Badges */
        .badges {
            display: flex;
            gap: 10px;
            justify-content: center;
            flex-wrap: wrap;
            margin-bottom: 20px;
        }
        
        .badge {
            display: inline-block;
            padding: 6px 12px;
            background: rgba(255,255,255,0.2);
            border-radius: 20px;
            font-size: 0.9em;
            border: 1px solid rgba(255,255,255,0.3);
            backdrop-filter: blur(10px);
        }
        
        .header .description {
            font-size: 1.1em;
            font-style: italic;
            opacity: 0.95;
            max-width: 700px;
            margin: 20px auto 0;
        }
        
        /* Main Content */
        .content {
            padding: 50px 40px;
        }
        
        .section {
            margin-bottom: 50px;
        }
        
        .section h2 {
            font-size: 2em;
            color: #667eea;
            margin-bottom: 20px;
            padding-bottom: 10px;
            border-bottom: 3px solid #667eea;
            display: inline-block;
        }
        
        .section h3 {
            font-size: 1.4em;
            color: #764ba2;
            margin-top: 25px;
            margin-bottom: 15px;
        }
        
        /* Description Section */
        .description-box {
            background: #f8f9fa;
            padding: 25px;
            border-left: 4px solid #667eea;
            border-radius: 8px;
            margin-bottom: 20px;
        }
        
        .description-box p {
            margin-bottom: 15px;
            line-height: 1.8;
            color: #555;
        }
        
        .description-box strong {
            color: #667eea;
        }
        
        /* Lists */
        ul, ol {
            margin-left: 25px;
            margin-bottom: 15px;
        }
        
        li {
            margin-bottom: 10px;
            color: #555;
            line-height: 1.7;
        }
        
        /* Architecture Diagram */
        .architecture {
            background: #f5f7ff;
            padding: 30px;
            border-radius: 10px;
            border: 2px solid #e0e7ff;
            margin: 20px 0;
            overflow-x: auto;
        }
        
        .architecture pre {
            font-family: 'Courier New', monospace;
            color: #333;
            font-size: 0.95em;
            line-height: 1.4;
        }
        
        /* Tables */
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            border-radius: 8px;
            overflow: hidden;
        }
        
        th {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 15px;
            text-align: left;
            font-weight: 600;
        }
        
        td {
            padding: 12px 15px;
            border-bottom: 1px solid #e0e7ff;
        }
        
        tr:hover {
            background: #f8f9fa;
        }
        
        tr:last-child td {
            border-bottom: none;
        }
        
        /* Roadmap */
        .roadmap-phase {
            background: white;
            border: 2px solid #e0e7ff;
            border-radius: 10px;
            padding: 20px;
            margin-bottom: 15px;
            border-left: 5px solid #667eea;
        }
        
        .roadmap-phase h4 {
            color: #667eea;
            margin-bottom: 12px;
            font-size: 1.1em;
        }
        
        .roadmap-phase ul {
            margin-left: 20px;
            list-style: none;
        }
        
        .roadmap-phase li {
            margin-bottom: 8px;
            color: #666;
        }
        
        .roadmap-phase li:before {
            content: "✓ ";
            color: #667eea;
            font-weight: bold;
            margin-right: 8px;
        }
        
        /* Status Box */
        .status-box {
            background: linear-gradient(135deg, #667eea15 0%, #764ba215 100%);
            border: 2px solid #667eea;
            border-radius: 10px;
            padding: 20px;
            margin: 20px 0;
        }
        
        .status-box strong {
            color: #667eea;
        }
        
        /* Code Block */
        .code-block {
            background: #2d2d2d;
            color: #f8f8f2;
            padding: 20px;
            border-radius: 8px;
            overflow-x: auto;
            margin: 15px 0;
            font-family: 'Courier New', monospace;
            font-size: 0.95em;
            line-height: 1.5;
        }
        
        /* Footer */
        .footer {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            text-align: center;
            padding: 40px 30px;
            margin-top: 50px;
        }
        
        .footer h3 {
            color: white;
            margin-bottom: 10px;
            font-size: 1.3em;
        }
        
        .footer p {
            font-style: italic;
            opacity: 0.95;
            font-size: 1.05em;
        }
        
        /* Utility Classes */
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin: 20px 0;
        }
        
        .card {
            background: #f8f9fa;
            padding: 20px;
            border-radius: 10px;
            border-left: 4px solid #667eea;
        }
        
        .card h4 {
            color: #667eea;
            margin-bottom: 10px;
        }
        
        .card p {
            color: #666;
            font-size: 0.95em;
        }
        
        /* Responsive */
        @media (max-width: 768px) {
            .header h1 {
                font-size: 2.5em;
            }
            
            .header .subtitle {
                font-size: 1.1em;
            }
            
            .content {
                padding: 30px 20px;
            }
            
            .section h2 {
                font-size: 1.6em;
            }
            
            table {
                font-size: 0.9em;
            }
            
            th, td {
                padding: 10px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <!-- Header -->
        <div class="header">
            <h1>🌍 DeustoAir</h1>
            <p class="subtitle">Sistema de gestión y consulta de datos de calidad del aire</p>
            <p class="project-info"><strong>Proyecto de Programación IV</strong></p>
            
            <div class="badges">
                <span class="badge">🔤 C</span>
                <span class="badge">⚙️ C++</span>
                <span class="badge">💾 SQLite</span>
                <span class="badge">🛠️ Eclipse</span>
                <span class="badge">🔄 En Desarrollo</span>
            </div>
            
            <p class="description">
                Aplicación <strong>cliente-servidor</strong> orientada a la <strong>administración</strong>, <strong>consulta</strong> y <strong>análisis</strong> de datos de calidad del aire
            </p>
        </div>
        
        <!-- Main Content -->
        <div class="content">
            <!-- Description Section -->
            <div class="section">
                <h2>📌 Descripción</h2>
                <div class="description-box">
                    <p>
                        <strong>DeustoAir</strong> es un proyecto académico desarrollado en el contexto de la asignatura <strong>Programación IV</strong>.
                    </p>
                    <p>
                        El objetivo es construir una <strong>aplicación modular</strong> basada en una arquitectura <strong>cliente-servidor</strong>, capaz de gestionar usuarios, consultar mediciones de calidad del aire y ofrecer estadísticas a partir de datos almacenados en una base de datos.
                    </p>
                </div>
                
                <h3>🏗️ Componentes del sistema</h3>
                <ul>
                    <li><strong>Administrador local (C):</strong> Gestión de usuarios, permisos y funciones administrativas</li>
                    <li><strong>Servidor remoto (C):</strong> Procesamiento de peticiones, acceso a base de datos y gestión de sockets</li>
                    <li><strong>Cliente remoto (C++):</strong> Consulta de datos y estadísticas por parte del usuario final</li>
                </ul>
            </div>
            
            <!-- Objectives Section -->
            <div class="section">
                <h2>🎯 Objetivos del proyecto</h2>
                <ul>
                    <li>Implementar una aplicación <strong>modular</strong> en C y C++</li>
                    <li>Gestionar <strong>usuarios, roles y permisos</strong> de forma segura</li>
                    <li>Consultar <strong>mediciones de calidad del aire</strong> en tiempo real</li>
                    <li>Obtener <strong>históricos y estadísticas avanzadas</strong></li>
                    <li>Utilizar <strong>SQLite</strong> como sistema de persistencia</li>
                    <li>Implementar comunicación mediante <strong>sockets TCP/IP</strong></li>
                    <li>Seguir una arquitectura realista separando cliente, servidor y administración local</li>
                </ul>
            </div>
            
            <!-- Architecture Section -->
            <div class="section">
                <h2>🧱 Arquitectura general</h2>
                <p>El sistema se organiza en una estructura cliente-servidor distribuida con administración local:</p>
                <div class="architecture">
                    <pre>                 +----------------------+
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
                            +------------> Servidor remoto</pre>
                </div>
            </div>
            
            <!-- Repository Structure -->
            <div class="section">
                <h2>🗂️ Estructura del repositorio</h2>
                <div class="code-block">
DeustoAir/
├── admin_local_c/
│   ├── src/
│   ├── include/
│   ├── data/
│   ├── logs/
│   └── Debug/
├── server_c/
├── docs/
└── README.md</div>
            </div>
            
            <!-- Technologies -->
            <div class="section">
                <h2>⚙️ Tecnologías utilizadas</h2>
                <table>
                    <thead>
                        <tr>
                            <th>Tecnología</th>
                            <th>Uso principal</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td><strong>C</strong></td>
                            <td>Administrador local y servidor remoto</td>
                        </tr>
                        <tr>
                            <td><strong>C++</strong></td>
                            <td>Cliente remoto</td>
                        </tr>
                        <tr>
                            <td><strong>SQLite</strong></td>
                            <td>Persistencia de datos y almacenamiento</td>
                        </tr>
                        <tr>
                            <td><strong>TCP/IP Sockets</strong></td>
                            <td>Comunicación cliente-servidor</td>
                        </tr>
                        <tr>
                            <td><strong>Eclipse IDE</strong></td>
                            <td>Entorno de desarrollo integrado</td>
                        </tr>
                    </tbody>
                </table>
            </div>
            
            <!-- Current Status -->
            <div class="section">
                <h2>🚧 Estado actual del proyecto</h2>
                <div class="status-box">
                    <p>
                        Actualmente se está desarrollando la <strong>base del módulo admin_local_c</strong>, incluyendo:
                    </p>
                    <ul>
                        <li>Estructura inicial del proyecto</li>
                        <li>Organización modular del código</li>
                        <li>Menú principal por consola</li>
                        <li>Preparación para registro e inicio de sesión</li>
                        <li>Configuración del entorno de compilación en Eclipse</li>
                    </ul>
                </div>
            </div>
            
            <!-- Roadmap -->
            <div class="section">
                <h2>🛣️ Roadmap</h2>
                
                <div class="roadmap-phase">
                    <h4>Fase 1 — Administración local y servidor base</h4>
                    <ul>
                        <li>Crear repositorio y estructura inicial</li>
                        <li>Configurar proyecto en Eclipse</li>
                        <li>Implementar menú principal inicial</li>
                        <li>Implementar registro de usuarios</li>
                        <li>Implementar inicio de sesión</li>
                        <li>Crear menú de gestión</li>
                        <li>Preparar integración con SQLite</li>
                        <li>Añadir gestión de usuarios y permisos</li>
                    </ul>
                </div>
                
                <div class="roadmap-phase">
                    <h4>Fase 2 — Cliente remoto y estadísticas</h4>
                    <ul>
                        <li>Implementar cliente remoto en C++</li>
                        <li>Añadir consultas por estación y municipio</li>
                        <li>Implementar rankings y estadísticas avanzadas</li>
                        <li>Comparativas entre municipios o regiones</li>
                        <li>Validación de permisos desde servidor</li>
                    </ul>
                </div>
            </div>
            
            <!-- Features -->
            <div class="section">
                <h2>👤 Funcionalidades previstas</h2>
                
                <h3>Administración local</h3>
                <ul>
                    <li>Registro de usuarios</li>
                    <li>Inicio de sesión seguro</li>
                    <li>Gestión de usuarios</li>
                    <li>Gestión de roles y permisos</li>
                    <li>Importación de datos</li>
                    <li>Borrado o reinicialización de base de datos</li>
                </ul>
                
                <h3>Cliente remoto</h3>
                <ul>
                    <li>Consulta de última medición por estación</li>
                    <li>Consulta de histórico por municipio</li>
                    <li>Estadísticas por contaminante</li>
                    <li>Rankings y comparativas</li>
                    <li>Visualización según nivel de permisos</li>
                </ul>
            </div>
            
            <!-- Compilation -->
            <div class="section">
                <h2>▶️ Compilación y ejecución</h2>
                <p>Actualmente el módulo <strong>admin_local_c</strong> se compila desde Eclipse con MinGW GCC.</p>
                
                <h3>Pasos generales</h3>
                <ol>
                    <li>Abrir el proyecto en Eclipse</li>
                    <li>Compilar usando la configuración Debug</li>
                    <li>Ejecutar la aplicación desde Eclipse</li>
                </ol>
                
                <div class="status-box">
                    <p>
                        <strong>Nota:</strong> Más adelante se añadirán instrucciones detalladas para compilar todos los módulos del sistema (servidor remoto y cliente remoto).
                    </p>
                </div>
            </div>
            
            <!-- Academic Context -->
            <div class="section">
                <h2>📚 Contexto académico</h2>
                <div class="description-box">
                    <p>
                        Este proyecto ha sido desarrollado como parte de la asignatura <strong>Programación IV</strong>, siguiendo una metodología por fases en la que se construye progresivamente una solución cliente-servidor completa.
                    </p>
                    <p>
                        El desarrollo incluye buenas prácticas de ingeniería de software, modularidad, arquitectura escalable y gestión de datos en tiempo real.
                    </p>
                </div>
            </div>
            
            <!-- Repository Status -->
            <div class="section">
                <h2>📝 Estado del repositorio</h2>
                <div class="status-box">
                    <p>
                        ⚠️ <strong>Este repositorio se encuentra en desarrollo activo.</strong>
                    </p>
                    <p>
                        La estructura, los módulos y las funcionalidades pueden evolucionar a medida que avance el proyecto.
                    </p>
                </div>
            </div>
        </div>
        
        <!-- Footer -->
        <div class="footer">
            <h3>✨ DeustoAir</h3>
            <p>Programación, sockets, SQLite y un poquito de sufrimiento controlado.</p>
        </div>
    </div>
</body>
</html>
