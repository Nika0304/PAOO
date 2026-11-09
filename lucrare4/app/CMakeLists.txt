cmake_minimum_required(VERSION 3.10)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# daca app e construit singur (nu din CMakeLists.txt-ul din radacina), adaug biblioteca de aici
if(NOT TARGET effectivelib)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../effectivelib ${CMAKE_BINARY_DIR}/effectivelib_build)
endif()

# ordinea fisierelor conteaza pentru demo-ul de la obiecte statice:
# globals_dir.cpp e inaintea lui globals_fs.cpp, deci obiectele din el se construiesc primele
add_executable(app main.cpp globals_dir.cpp globals_fs.cpp)
target_link_libraries(app PRIVATE effectivelib)

if(MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra)
endif()
