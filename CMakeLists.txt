cmake_minimum_required(VERSION 3.5)
 
project(tabletop_lancer)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_library(lib $ENV{HOME}/tabletop_lancer/src/lib/texture.cpp)
add_library(gamelib 
            $ENV{HOME}/tabletop_lancer/src/gamelib/tile.cpp 
            $ENV{HOME}/tabletop_lancer/src/gamelib/hex_map.cpp)

add_executable(tabletop_lancer src/main.cpp)

target_link_libraries(gamelib lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(tabletop_lancer ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} lib gamelib)