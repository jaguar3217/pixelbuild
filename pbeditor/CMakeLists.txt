file(GLOB pbeditor_SRC
	"*.hpp"
	"*.cpp"
)

find_package(Qt4 REQUIRED)
add_executable(pbeditor ${pbeditor_SRC})
target_link_libraries(pbeditor LINK_PUBLIC pbengine)
target_link_libraries(pbeditor LINK_PRIVATE sfml-system sfml-network)
target_link_libraries(pbeditor LINK_PRIVATE Qt4::QtGui Qt4::QtDBus)

IF(NOT WIN32 AND NOT APPLE)
find_package(X11 REQUIRED)
add_definitions(-DCMAKE_HAS_X)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(pbeditor PUBLIC ${X11_LIBRARIES})
ENDIF()

IF(WIN32)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") # for WinMain to work
set_property(TARGET pbeditor PROPERTY VS_DPI_AWARE "PerMonitor") # for SFML to work
# wxWidgets Resources
target_sources(pbeditor PRIVATE ${wxWidgets_INCLUDE_DIRS}/wx/msw/wx.rc)
ENDIF()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plrsheet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tileset.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.pblvl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
