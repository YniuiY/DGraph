cmake_minimum_required(VERSION 3.1)

project(DGraph)

IF(DEFINED COMPILE_TOOLCHAIN_ROOT)
  message("compile ARM, targetf ${COMPILE_TOOLCHAIN_ROOT}")
  add_definitions("-O2")
  set(TEST_COMPILER_ROOT "${COMPILE_TOOLCHAIN_ROOT}/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin")

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_PROCESSOR arm)

  set(CMAKE_CXX_COMPILER ${TEST_COMPILER_ROOT}/aarch64-linux-gnu-g++)
  set(CMAKE_C_COMPILER ${TEST_COMPILER_ROOT}/aarch64-linux-gnu-gcc)

  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g2 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")

  link_directories(${PROJECT_SOURCE_DIR}/3rd-party/ThreadPool/arm_lib)
ELSEIF(DEFINED COMPILE_TOOLCHAIN_ROOT_10_3_1)
  set(TOOLCHAIN_COMPILER "gcc-10.3-2021.07-x86_64-aarch64-none-linux-gnu")
  message(STATUS "Compile ARM, targetfs ${COMPILE_TOOLCHAIN_ROOT_10_3_1}")
  message(STATUS "Compile ARM, toolchain ${TOOLCHAIN_COMPILER}")
  add_definitions("-O2")
  set(TOOLCHAIN_COMPILER_ROOT "${COMPILE_TOOLCHAIN_ROOT_10_3_1}/${TOOLCHAIN_COMPILER}/bin")

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_PROCESSOR arm)
  set(CMAKE_SYSTEM_PLATFORM aarch64)
  set(CMAKE_GCC_VERSION 10.3.1)

  set(CMAKE_CXX_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-none-linux-gnu-g++)
  set(CMAKE_C_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-none-linux-gnu-gcc)

  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g2 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
ELSEIF(DEFINED COMPILE_TOOLCHAIN_ROOT_12_1_1)
  set(TOOLCHAIN_COMPILER "gcc-12.1-2022.08-cortex-a53-aarch64-linux5.15")
  message(STATUS "Compile ARM, targetfs ${COMPILE_TOOLCHAIN_ROOT_12_1_1}")
  message(STATUS "Compile ARM, toolchain ${TOOLCHAIN_COMPILER}")
  set(CMAKE_BUILD_TYPE Release)
  # set(CMAKE_BUILD_TYPE Debug)
  set(TOOLCHAIN_COMPILER_ROOT "${COMPILE_TOOLCHAIN_ROOT_12_1_1}/${TOOLCHAIN_COMPILER}/bin")

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_PROCESSOR arm)

  set(CMAKE_CXX_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-linux-gnu-g++)
  set(CMAKE_C_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-linux-gnu-gcc)

  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g2 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
ELSE()
  link_directories(${PROJECT_SOURCE_DIR}/3rd-party/ThreadPool/x86_lib)
  link_directories(${PROJECT_SOURCE_DIR}/3rd-party/spdlog/lib)
  # add_definitions("-Wall -g")
  # add_definitions("-Wall -O2")
ENDIF()


option(INSTALL "install" ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(./include)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/ThreadPool/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/spdlog/include)

aux_source_directory(./src SRCS)
aux_source_directory(./src/ParamManager PARAM_SRCS)
aux_source_directory(./src/Region REGION_SRCS)
aux_source_directory(./src/Utils UTIL_SRCS)

add_library(dgraph SHARED ${SRCS} ${PARAM_SRCS} ${REGION_SRCS} ${UTIL_SRCS})

target_link_libraries(dgraph thread_pool pthread spdlog)

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/output/DGraph")
  message("install to ${OUTPUT}")
  install(TARGETS dgraph LIBRARY DESTINATION ${OUTPUT}/lib)
  if (DEFINED COMPILE_TOOLCHAIN_ROOT)
    install(FILES ${PROJECT_SOURCE_DIR}/3rd-party/ThreadPool/arm_lib/libthread_pool.so DESTINATION ${OUTPUT}/lib)
  else()
    install(FILES ${PROJECT_SOURCE_DIR}/3rd-party/ThreadPool/x86_lib/libthread_pool.so DESTINATION ${OUTPUT}/lib)
  endif()
  install(FILES ${PROJECT_SOURCE_DIR}/include/DGraph.h DESTINATION ${OUTPUT}/include)
  install(FILES ${PROJECT_SOURCE_DIR}/include/Node.h DESTINATION ${OUTPUT}/include)
  install(FILES ${PROJECT_SOURCE_DIR}/include/GraphManager.h DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ParamManager DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/RingBuffer DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/Region DESTINATION ${OUTPUT}/include)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/Utils DESTINATION ${OUTPUT}/include)
endif()