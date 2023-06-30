cmake_minimum_required(VERSION 3.1)

project(DGraph)

set(CMAKE_CXX_STANDARD 14)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/bin)

link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(./include)

aux_source_directory(./src SRCS)

add_executable(run ${SRCS})

target_link_libraries(run pthread)

# target_link_libraries(run ThreadPool pthread)