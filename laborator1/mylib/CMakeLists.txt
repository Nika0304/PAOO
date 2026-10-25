cmake_minimum_required(VERSION 3.10)
project(mylib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Biblioteca statica (libmylib.a pe Linux/macOS, mylib.lib pe Windows)
add_library(mylib STATIC src/mylib.cpp)

# Header-ul din include/ este vizibil si pentru proiectele care folosesc biblioteca
target_include_directories(mylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
