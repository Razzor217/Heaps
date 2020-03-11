set(SOURCES 
    ./main.cpp
)

set(HEADERS
    ./interface/IHeap.h
    ./Interface/INode.h

    ./FibonacciHeap/FibonacciHeap.h
    ./FibonacciHeap/FibonacciHeap.hpp
    ./PairingHeap/PairingHeap.h
    ./PairingHeap/PairingHeap.hpp
)

add_executable(heaps ${HEADERS} ${SOURCES})