cmake_minimum_required(VERSION 3.10)
project(tema3 LANGUAGES CXX)

# Ordinea conteaza: biblioteca se construieste inainte de aplicatia care o foloseste
add_subdirectory(arraylib)
add_subdirectory(app)
