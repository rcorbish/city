cmake_minimum_required (VERSION 3.13)

project (city LANGUAGES CXX)

find_package( OpenGL REQUIRED COMPONENTS OpenGL )
find_package( GLUT REQUIRED )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}  )

file(GLOB_RECURSE CITY_SOURCE_FILES
    CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
)

add_compile_options( -std=c++17 )
add_compile_options( -g )

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} . )
include_directories( src src/shapes stb )

add_executable( city ${CITY_SOURCE_FILES} )

target_link_libraries( city ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} )
