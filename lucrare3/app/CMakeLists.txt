cmake_minimum_required(VERSION 3.10)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# biblioteca statica din ../arraylib se adauga aici.
if(NOT TARGET arraylib)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../arraylib ${CMAKE_BINARY_DIR}/arraylib_build)
endif()

add_executable(app main.cpp)
target_link_libraries(app PRIVATE arraylib) #leaga aplicati de bibliotaca si ii aduce automat si calea catre hader e

if(MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra)
endif()
