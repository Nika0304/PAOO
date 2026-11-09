cmake_minimum_required(VERSION 3.10)
project(laborator1 LANGUAGES CXX)

# Ordinea conteaza: biblioteca se construieste inainte de aplicatia care o foloseste
add_subdirectory(mylib)
add_subdirectory(app)
