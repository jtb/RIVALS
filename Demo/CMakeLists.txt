include_directories(${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/Mem ${RIVALS_SOURCE_DIR}/FileUtils ${RIVALS_SOURCE_DIR}/Iterators)

link_directories (${RIVALS_BINARY_DIR}/Utils ${RIVALS_BINARY_DIR}/Mem ${RIVALS_BINARY_DIR}/FileUtils ${RIVALS_BINARY_DIR}/Iterators)

add_executable (rivalsDemo test.cpp) 

target_link_libraries (rivalsDemo Utils FileUtils Iterators debug Mem)
