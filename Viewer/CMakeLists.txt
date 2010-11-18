cmake_minimum_required (VERSION 2.6)

include_directories(${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/FileUtils ${RIVALS_SOURCE_DIR}/Iterators)
link_directories (${RIVALS_BINARY_DIR}/Utils ${RIVALS_BINARY_DIR}/FileUtils ${RIVALS_BINARY_DIR}/Iterators)

FIND_LIBRARY(GLUT_LIBRARY GLUT )
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
SET(EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY})

add_executable(plot plot.cpp)
target_link_libraries(plot ${EXTRA_LIBS} Utils FileUtils Iterators)
