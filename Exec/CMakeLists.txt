include_directories(${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/Mem ${RIVALS_SOURCE_DIR}/FileUtils ${RIVALS_SOURCE_DIR}/Iterators ${RIVALS_SOURCE_DIR}/Lua)

link_directories (${RIVALS_BINARY_DIR}/Utils ${RIVALS_BINARY_DIR}/Mem ${RIVALS_BINARY_DIR}/FileUtils ${RIVALS_BINARY_DIR}/Iterators ${RIVALS_BINARY_DIR}/Lua)

add_executable (rivals interp.cpp) 

target_link_libraries (rivals Utils FileUtils Iterators Lua debug Mem)
