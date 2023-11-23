# CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

project(Batalla_naval)

# Establecer la versión de C++ a C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agrega los archivos de código fuente
file(GLOB SOURCES "lib/src/*.cpp")

# Agrega los archivos de encabezado
include_directories("lib/headers")

# Configuración del ejecutable
add_executable(Batalla_naval main.cpp ${SOURCES} )
