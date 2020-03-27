include_directories(${Heaps_SOURCE_DIR}/source)

set(HEADERS
    interface/IHeap.h
    interface/INode.h

    FibonacciHeap/FibonacciHeap.h
    FibonacciHeap/FibonacciHeap.hpp
    PairingHeap/PairingHeap.h
    PairingHeap/PairingHeap.hpp
)

add_library(HeapLibs ${HEADERS})

set_target_properties(HeapLibs PROPERTIES LINKER_LANGUAGE CXX)

add_executable(heaps main.cpp)

target_link_libraries(heaps HeapLibs)