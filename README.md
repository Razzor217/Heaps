# Heaps

This project provides [interfaces](source/interface) for heap data structures 
as well as implementations of 
[Fibonacci Heaps](source/FibonacciHeap/FibonacciHeap.h) and 
[Pairing Heaps](source/PairingHeap/PairingHeap.h). 

Heaps provide the same basic operations `insert`, `size`, `min` and `deleteMin` 
as priority queues with the addition of the operations `remove`, `decreaseKey` 
and `merge`. Additionally, heaps focus on good asymptotic performance for the 
most of those operations. For example, Fibonacci Heaps achieve amortized 
constant time for all operations but deletions; those are achieved in amortized 
logarithmic time.

## Build and Documentation

To build this project, first create a Makefile with cmake and compile:

    $ cd <heaps directory>
    $ mkdir build
    $ cd build
    $ cmake .. && make

The API documentation is provided with DoxyGen and can be built with

    $ make doc

from within the `build` directory. To view the documentation, simply open 
`<heaps directory>/build/doc/index.html` in your preferred browser.
