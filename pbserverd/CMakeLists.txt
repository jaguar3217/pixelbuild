add_executable(pbserverd main.cpp)

target_link_libraries(pbserverd LINK_PUBLIC libpbengine)
target_link_libraries(pbserverd LINK_PRIVATE sfml-system sfml-network)