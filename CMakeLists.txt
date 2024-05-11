cmake_minimum_required(VERSION 3.1)

project(DGraph)

set(CMAKE_CXX_STANDARD 14)

# add_definitions("-Wall -g")

option(INSTALL "install" ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(./include)

aux_source_directory(./src SRCS)
aux_source_directory(./src/threadpool TP_SRCS)
aux_source_directory(./src/ParamManager PARAM_SRCS)
aux_source_directory(./src/Utils UTIL_SRCS)

add_library(dgraph SHARED ${SRCS} ${TP_SRCS} ${PARAM_SRCS} ${UTIL_SRCS})

target_link_libraries(dgraph pthread)

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/output/DGraph")
  message("install to ${OUTPUT}")
  install(TARGETS dgraph LIBRARY DESTINATION ${OUTPUT}/lib)
  install(FILES ${PROJECT_SOURCE_DIR}/include/DGraph.h DESTINATION ${OUTPUT}/include)
  install(FILES ${PROJECT_SOURCE_DIR}/include/Node.h DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ParamManager DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/Utils DESTINATION ${OUTPUT}/include)
endif()