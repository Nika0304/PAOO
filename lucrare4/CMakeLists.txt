cmake_minimum_required(VERSION 3.10)
project(lucrare4 LANGUAGES CXX)

# biblioteca se construieste inainte de aplicatia care o foloseste
add_subdirectory(effectivelib)
add_subdirectory(app)
