# C++ Microservice

> Un microservicio RESTful en C++ que implementa Arquitectura Hexagonal con Oat++

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.11+-green.svg)](https://cmake.org/)
[![Oat++](https://img.shields.io/badge/Oat++-1.2.5-orange.svg)](https://oatpp.io/)
[![Linux](https://img.shields.io/badge/Platform-Linux-lightgrey.svg)](https://www.linux.org/)

## 📋 Descripción

Este proyecto es un ejemplo de microservicio construido en C++ que implementa **Arquitectura Hexagonal** (también conocida como Puertos y Adaptadores). El objetivo es demostrar cómo aplicar principios de Clean Architecture en C++ moderno, logrando un código desacoplado, testeable y mantenible.

### Arquitectura Hexagonal

![Hexagonal Architecture](https://github.com/rquiroga83/cpp_microservice/blob/main/docu/1_kEomMfgNPu1srEAH7-Z_LA.png)

La arquitectura se divide en tres capas principales:

```
┌─────────────────────────────────────────┐
│         Adapters (External)             │
│  ┌──────────────┐  ┌─────────────────┐  │
│  │ Controllers  │  │  Repositories   │  │
│  │   (HTTP)     │  │   (Database)    │  │
│  └──────┬───────┘  └────────┬────────┘  │
│         │                   │           │
└─────────┼───────────────────┼───────────┘
          │                   │
┌─────────┼───────────────────┼───────────┐
│         ▼                   ▼           │
│  ┌──────────────┐  ┌─────────────────┐  │
│  │    Ports     │  │     Ports       │  │
│  │  (UseCase)   │  │  (Repository)   │  │
│  └──────┬───────┘  └────────▲────────┘  │
│         │                   │           │
│         ▼                   │           │
│  ┌─────────────────────────┬┘           │
│  │       Services          │            │
│  │    (Business Logic)     │            │
│  └─────────────────────────┘            │
│              ▲                          │
│              │                          │
│        ┌─────┴──────┐                   │
│        │   Domain   │                   │
│        │  (Entities)│                   │
│        └────────────┘                   │
│                                         │
│           Core (Application)            │
└─────────────────────────────────────────┘
```

## 🏗️ Estructura del Proyecto

```
cpp_microservice/
├── src/
│   ├── App.cpp                      # Punto de entrada de la aplicación
│   ├── AppComponent.hpp             # Configuración de componentes Oat++
│   ├── ServiceLocator.hpp           # Sistema de inyección de dependencias
│   ├── SLModules.cpp                # Módulos del Service Locator
│   │
│   ├── core/                        # Capa de dominio y lógica de negocio
│   │   ├── domain/
│   │   │   └── User.cpp             # Entidad de dominio User
│   │   ├── ports/
│   │   │   ├── UserRepository.cpp   # Interfaz del repositorio (puerto)
│   │   │   └── UserUseCase.cpp      # Interfaz de caso de uso (puerto)
│   │   └── services/
│   │       └── UserService.cpp      # Implementación de la lógica de negocio
│   │
│   └── adapters/                    # Adaptadores externos
│       ├── controllers/
│       │   ├── UserController.cpp   # Controlador REST API
│       │   ├── UserController.hpp
│       │   └── dto/
│       │       └── DTOs.hpp         # Data Transfer Objects
│       └── repositories/
│           └── UserRepositoryImpl.cpp  # Implementación del repositorio
│
├── CMakeLists.txt                   # Configuración de compilación
└── README.md
```

## 🎯 Características

- ✅ **Arquitectura Hexagonal**: Separación clara entre lógica de negocio y detalles de implementación
- ✅ **API RESTful**: Endpoints HTTP usando Oat++
- ✅ **Inyección de Dependencias**: Service Locator pattern para gestión de dependencias
- ✅ **C++ Moderno**: Utiliza C++17 con smart pointers y buenas prácticas
- ✅ **DTOs**: Serialización/deserialización automática de JSON
- ✅ **Puertos y Adaptadores**: Fácil de testear y extender

## 🔧 Requisitos Previos

- **SO**: Linux (Ubuntu/Debian recomendado)
- **Compilador**: GCC 10+ o Clang con soporte C++17
- **Build System**: CMake 3.11 o superior
- **Dependencias**: Oat++ 1.2.5+

## 📦 Instalación

### 1. Instalar herramientas de compilación

```bash
sudo apt-get update
sudo apt-get install build-essential gcc-10 g++-10 cmake
```

### 2. Instalar Oat++

Oat++ es el framework principal del proyecto. Sigue las instrucciones oficiales:

**Opción A: Desde repositorios (Ubuntu)**
```bash
# Agregar repositorio
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:lganzzzo/oatpp
sudo apt-get update

# Instalar Oat++
sudo apt-get install liboatpp-dev
```

**Opción B: Compilar desde fuente**
```bash
git clone https://github.com/oatpp/oatpp.git
cd oatpp
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

🔗 **Documentación oficial**: 
- [Instalación en Linux](https://oatpp.io/docs/installation/unix-linux/#ubuntu)
- [Tutorial paso a paso](https://oatpp.io/docs/start/step-by-step/#simplest-project)

### 3. Instalar dependencias adicionales (opcional)

```bash
sudo apt-get install libcpprest-dev nlohmann-json3-dev
```

## 🚀 Compilación y Ejecución

### Compilar el proyecto

```bash
# En el directorio raíz del proyecto
cmake .
make
```

Esto generará el ejecutable `cpp-microservice-exe`.

### Ejecutar el servidor

```bash
./cpp-microservice-exe
```

El servidor se iniciará en `http://0.0.0.0:8000`

Deberías ver un mensaje similar a:
```
Server running on port 8000
```

## 📡 API Endpoints

### Obtener usuario por ID

**Endpoint**: `GET /users/{userId}`

**Ejemplo de uso**:
```bash
curl http://localhost:8000/users/123
```

**Respuesta exitosa** (HTTP 200):
```json
{
  "id": 123,
  "name": "Thomas Anderson",
  "email": "neo@matrix.com",
  "statusCode": 200
}
```

### Verificar estado del servidor

**Endpoint**: `GET /`

```bash
curl http://localhost:8000/
```

## 🏛️ Explicación de la Arquitectura

### Capa de Dominio (Core)

**`User` (Entidad)**
- Representa la entidad de negocio principal
- Contiene los atributos: `id`, `name`, `email`
- Sin dependencias externas

### Capa de Puertos (Interfaces)

**`UserRepository` (Puerto)**
- Define el contrato para acceso a datos
- Método: `findById(long id)`

**`UserUseCase` (Puerto)**
- Define los casos de uso de negocio
- Método: `getUserById(long id)`

### Capa de Servicios

**`UserService`**
- Implementa `UserUseCase`
- Contiene la lógica de negocio
- Depende de `UserRepository` (inyección de dependencias)

### Capa de Adaptadores

**`UserController`**
- Adaptador de entrada (HTTP)
- Maneja las peticiones REST
- Convierte entre DTOs y entidades de dominio

**`UserRepositoryImpl`**
- Adaptador de salida (Persistencia)
- Implementa `UserRepository`
- Actualmente retorna datos mock (puede conectarse a una BD real)

### Inyección de Dependencias

El proyecto utiliza un **Service Locator** personalizado:

```cpp
// Configuración en SLModules.cpp
class RepositoriesSLModule : public ServiceLocator::Module {
  void load() override {
    bind<UserRepository>("UserService").to<UserRepositoryImpl>(...);
  }
};

class ServicesSLModule : public ServiceLocator::Module {
  void load() override {
    bind<UserUseCase>("UserService").to<UserService>(...);
  }
};
```

## 🧪 Testing

Para probar el endpoint manualmente:

```bash
# Con curl
curl http://localhost:8000/users/1

# Con httpie (si está instalado)
http GET http://localhost:8000/users/1

# Desde el navegador
# Visita: http://localhost:8000/users/1
```

## 🔄 Extensión del Proyecto

### Agregar un nuevo endpoint

1. Define el método en `UserController.hpp`
2. Implementa la lógica en `UserService.cpp`
3. Actualiza el puerto `UserUseCase` si es necesario

### Conectar a una base de datos real

1. Modifica `UserRepositoryImpl.cpp`
2. Agrega la biblioteca de la BD (ej: libpq para PostgreSQL)
3. Implementa `findById()` con queries reales

### Agregar nuevas entidades

1. Crea la entidad en `core/domain/`
2. Define los puertos en `core/ports/`
3. Implementa el servicio en `core/services/`
4. Crea los adaptadores correspondientes

## 📚 Recursos y Referencias

- [Oat++ Documentation](https://oatpp.io/docs/start/)
- [Hexagonal Architecture - Alistair Cockburn](https://alistair.cockburn.us/hexagonal-architecture/)
- [Clean Architecture - Robert C. Martin](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)
- [C++17 Reference](https://en.cppreference.com/w/cpp/17)

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto es un ejemplo educativo de código abierto.

## 👤 Autor

**rquiroga83**

---

⭐ Si este proyecto te resultó útil, considera darle una estrella en GitHub
