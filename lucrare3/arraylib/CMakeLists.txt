cmake_minimum_required(VERSION 3.10)
project(arraylib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Biblioteca statica (libarraylib.a pe Linux/macOS, arraylib.lib pe Windows)
add_library(arraylib STATIC
    src/int_array.cpp
    src/bad_examples.cpp
)

# Header-ele din include/ sunt vizibile si pentru proiectele care folosesc biblioteca
target_include_directories(arraylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(arraylib PRIVATE /W4)
else()
    target_compile_options(arraylib PRIVATE -Wall -Wextra)
endif()
