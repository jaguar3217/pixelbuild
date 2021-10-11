cmake_minimum_required(VERSION 2.8.11)
project(Pixelbuild)

find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)

add_subdirectory(libpbengine)
add_subdirectory(pbclient)
add_subdirectory(pbserverd)