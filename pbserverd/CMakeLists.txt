add_executable(pbserverd main.cpp)

target_link_libraries(pbserverd LINK_PUBLIC pbengine)
target_link_libraries(pbserverd LINK_PRIVATE sfml-system sfml-network)