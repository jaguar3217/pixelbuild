#file(GLOB pbeditor_SRC
#	"*.hpp"
#	"*.cpp"
#)

#add_executable(pbeditor ${pbeditor_SRC})
add_executable(pbeditor MainApplication.cpp)
target_link_libraries(pbeditor LINK_PUBLIC pbengine)
target_link_libraries(pbeditor LINK_PRIVATE sfml-system sfml-network)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

target_include_directories(pbeditor PUBLIC ${wxWidgets_INCLUDE_DIRS})
target_compile_definitions(pbeditor PUBLIC ${wxWidgets_DEFINITIONS})
target_compile_options(pbeditor PRIVATE ${wxWidgets_CXX_FLAGS})
target_link_libraries(pbeditor PUBLIC ${wxWidgets_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
# for WinMain to work