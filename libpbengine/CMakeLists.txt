add_library(libpbengine libpbengine.cpp)

target_include_directories(libpbengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(libpbengine sfml-graphics sfml-window sfml-system sfml-network)