cmake_minimum_required(VERSION 3.3)

# if(NOT DEFINED QMK_ROOT)

project(qmk_firmware)

include(ExternalProject)
ExternalProject_Add(mntre
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/keyboards/mntre
  TMP_DIR ${CMAKE_SOURCE_DIR}/build
  CMAKE_GENERATOR "MinGW Makefiles"
  CMAKE_ARGS 
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/platforms/avr/toolchain.cmake
    -DQMK_ROOT=${CMAKE_CURRENT_SOURCE_DIR}
)

# else()

# add_subdirectory()

# endif()