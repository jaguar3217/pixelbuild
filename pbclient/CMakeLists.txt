file(GLOB pbclient_SRC
	"*.hpp"
	"*.cpp"
)

add_executable(pbclient ${pbclient_SRC})

target_link_libraries(pbclient LINK_PUBLIC pbengine)
target_link_libraries(pbclient LINK_PRIVATE sfml-graphics sfml-window sfml-system sfml-network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plrsheet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tileset.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})