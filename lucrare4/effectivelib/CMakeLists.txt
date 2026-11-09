cmake_minimum_required(VERSION 3.10)
project(effectivelib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# biblioteca statica (libeffectivelib.a pe Linux)
add_library(effectivelib STATIC
    src/tracer.cpp
    src/point.cpp
    src/entry.cpp
    src/init_order.cpp
    src/file_system.cpp
    src/generated.cpp
    src/home_for_sale.cpp
)

# header-ele din include/ sunt vizibile si pentru aplicatia care foloseste biblioteca
target_include_directories(effectivelib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(effectivelib PRIVATE /W4)
else()
    target_compile_options(effectivelib PRIVATE -Wall -Wextra)
endif()
