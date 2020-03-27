find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(
    ${Heaps_SOURCE_DIR}/source
    ${BOOST_INCLUDE_DIRS}
)

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(pairingHeapTest PairingHeap/PairingHeapTest.cpp)
add_executable(fibonacciHeapTest FibonacciHeap/FibonacciHeapTest.cpp)

target_link_libraries(
    pairingHeapTest
    HeapLibs
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries(
    fibonacciHeapTest
    HeapLibs
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(NAME PairingHeapTest COMMAND pairingHeapTest)
add_test(NAME FibonacciHeapTest COMMAND fibonacciHeapTest)