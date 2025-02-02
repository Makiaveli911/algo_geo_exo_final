cmake_minimum_required(VERSION 3.24)
project(algo_geo_4)

set(CMAKE_CXX_STANDARD 20)

add_executable(algo_geo_4 main.cpp affichage.cpp point.cpp carte.cpp winbgi.cpp triangulation.cpp Hohneck.txt createObj.cpp)

# Inclure le dossier des fichiers d'en-tête
include_directories(include)

# Lier SFML aux bibliothèques
target_link_libraries(algo_geo_4 gdi32 user32 kernel32)
