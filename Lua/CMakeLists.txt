include_directories(${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/FileUtils ${RIVALS_SOURCE_DIR}/Iterators)

link_directories (${RIVALS_BINARY_DIR}/Utils ${RIVALS_BINARY_DIR}/FileUtils ${RIVALS_BINARY_DIR}/Iterators /Users/barybrown/Rivals081710/Lua/lib)

add_executable (luatest luatree.cpp) 

target_link_libraries (luatest Utils FileUtils Iterators lua)
