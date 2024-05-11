cmake_minimum_required(VERSION 3.1)

project(Sample)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-Wall -g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/../output/DGraph/lib)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/../output/DGraph/include)


set(DGRAPH_TUTORIAL_LIST
  sample
  sample-region
)

foreach(tut ${DGRAPH_TUTORIAL_LIST})
    add_executable(${tut} ./src/${tut}.cpp)
    target_link_libraries(${tut} dgraph pthread)
endforeach()