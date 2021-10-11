add_executable(pbclient main.cpp)

target_link_libraries(pbclient LINK_PUBLIC libpbengine)
target_link_libraries(pbclient LINK_PRIVATE sfml-graphics sfml-window sfml-system sfml-network)