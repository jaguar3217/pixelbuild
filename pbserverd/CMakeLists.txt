file(GLOB pbserverd_SRC
	"*.hpp"
	"*.cpp"
)

add_executable(pbserverd ${pbserverd_SRC})

target_link_libraries(pbserverd LINK_PUBLIC pbengine)
target_link_libraries(pbserverd LINK_PRIVATE sfml-system sfml-network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.pblvl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
