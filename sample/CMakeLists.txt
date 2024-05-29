cmake_minimum_required(VERSION 3.1)

project(Sample)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-Wall -g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 下面两条可以使编译出的可执行程序自动连接上动态库
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--disable-new-dtags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--disable-new-dtags")

link_directories(${PROJECT_SOURCE_DIR}/../output/DGraph/lib)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/../output/DGraph/include)


set(DGRAPH_TUTORIAL_LIST
  sample
  sample-region
  sample-fvp
  sample-2_task
)

foreach(tut ${DGRAPH_TUTORIAL_LIST})
    add_executable(${tut} ./src/${tut}.cpp)
    target_link_libraries(${tut} dgraph thread_pool pthread)
endforeach()