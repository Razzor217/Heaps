cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(Heaps)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    #set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    #set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    #configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    #message("Doxygen build started")

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/../Doxyfile#${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Package Doxygen not found!")
endif (DOXYGEN_FOUND)

add_subdirectory(source)