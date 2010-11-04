cmake_minimum_required (VERSION 2.6) 
project(RIVALS)

IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  ADD_DEFINITIONS(-DDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

add_subdirectory(Utils)
add_subdirectory(Mem)
add_subdirectory(FileUtils)
add_subdirectory(Iterators)
add_subdirectory(Demo)
add_subdirectory(Lua)
add_subdirectory(Exec)
