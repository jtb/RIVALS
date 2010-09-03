include_directories (${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/FileUtils)
add_library (Iterators iterator.cpp overlaps.cpp strand.cpp interval_iter.cpp contained_in.cpp no_nests.cpp clique.cpp flatten.cpp merge.cpp range.cpp sample.cpp) 
