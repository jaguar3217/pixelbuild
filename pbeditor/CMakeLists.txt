file(GLOB pbeditor_SRC
	"*.hpp"
	"*.cpp"
)

add_executable(pbeditor ${pbeditor_SRC})
target_link_libraries(pbeditor LINK_PUBLIC pbengine)
target_link_libraries(pbeditor LINK_PRIVATE sfml-system sfml-network)

find_package(wxWidgets REQUIRED gl core aui base OPTIONAL_COMPONENTS net)

target_include_directories(pbeditor PUBLIC ${wxWidgets_INCLUDE_DIRS})
target_compile_definitions(pbeditor PUBLIC ${wxWidgets_DEFINITIONS})
target_compile_options(pbeditor PRIVATE ${wxWidgets_CXX_FLAGS})
target_link_libraries(pbeditor PUBLIC ${wxWidgets_LIBRARIES})

IF(NOT WIN32 AND NOT APPLE)
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
IF(NOT GTK3_INCLUDE_DIRS)
    MESSAGE(FATAL_ERROR "Could not find gtk3")
ENDIF()
# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0 gdk-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Link the target to the GTK+ libraries
target_link_libraries(pbeditor PUBLIC ${GTK3_LIBRARIES})
include_directories(${GDK_INCLUDE_DIRS})
link_directories(${GDK_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GDK_CFLAGS_OTHER})
# Link the target to the GTK+ libraries
target_link_libraries(pbeditor PUBLIC ${GDK_LIBRARIES})

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