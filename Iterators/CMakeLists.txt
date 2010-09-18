include_directories (${RIVALS_SOURCE_DIR}/Utils ${RIVALS_SOURCE_DIR}/FileUtils)
add_library (Iterators iterators.cpp overlaps.cpp strand.cpp interval_iter.cpp contained_in.cpp contains.cpp no_nests.cpp nested.cpp clique.cpp flatten.cpp merge.cpp range.cpp sample.cpp rivalfile.cpp rivals.cpp) 
