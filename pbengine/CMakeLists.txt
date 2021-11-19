file(GLOB pbengine_SRC
    "*.h"
    "*.hpp"
    "*.cpp"
)

add_library(pbengine SHARED ${pbengine_SRC})

target_include_directories(pbengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pbengine sfml-graphics sfml-window sfml-system sfml-network)