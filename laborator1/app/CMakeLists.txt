cmake_minimum_required(VERSION 3.10)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Daca proiectul este construit de sine statator (nu din CMakeLists.txt-ul radacina),
# biblioteca statica din ../mylib se adauga aici.
if(NOT TARGET mylib)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../mylib ${CMAKE_BINARY_DIR}/mylib_build)
endif()

add_executable(app main.cpp)
target_link_libraries(app PRIVATE mylib)
