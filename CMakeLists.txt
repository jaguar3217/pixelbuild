cmake_minimum_required(VERSION 3.0.0)
project(Pixelbuild)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)

add_subdirectory(pbengine)
add_subdirectory(pbclient)
add_subdirectory(pbserverd)