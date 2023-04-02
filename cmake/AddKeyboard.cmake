macro(add_keyboard KEYBOARD_CMAKE)
  get_filename_component(KEYBOARD_FULL_DIRECTORY "${KEYBOARD_CMAKE}" DIRECTORY)

  # find the right toolchain
  file(READ ${KEYBOARD_FULL_DIRECTORY}/info.json JSON_STRING)
  string(JSON PROCESSOR GET ${JSON_STRING} processor)
  if(${PROCESSOR} MATCHES "^at.*")
    set(PLATFORM "avr")
    # find_package(avr-gcc)
  elseif(
    ${PROCESSOR} MATCHES "^STM.*" OR
    ${PROCESSOR} MATCHES "^WB32.*" OR
    ${PROCESSOR} MATCHES "^MK.*" OR
    ${PROCESSOR} MATCHES "RP2040" OR
    ${PROCESSOR} MATCHES "^GD32.*")
    set(PLATFORM "chibios")
  endif()
  if(NOT DEFINED PLATFORM)
    message(FATAL_ERROR "Could not find platform for ${KEYBOARD_FULL_DIRECTORY}")
  endif()

  include(FindToolChain)
  find_toolchain()

  file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FULL_DIRECTORY}")
  string(REPLACE "/" "." KEYBOARD_NAME ${KEYBOARD_FOLDER})
  ExternalProject_Add(${KEYBOARD_NAME}
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    PREFIX ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}
    TMP_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/tmp
    DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/Download
    BINARY_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/Build
    STAMP_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/Stamp
    LOG_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/Log
    INSTALL_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}/Install
    INSTALL_COMMAND cmake -E echo "No install needed"
    # this seems to work well for all systems so far - not sure if it'd be useful to customize
    CMAKE_GENERATOR "Unix Makefiles"
    CMAKE_ARGS 
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/platforms/${PLATFORM}/toolchain.cmake
      -DTOOLCHAIN_ROOT=${TOOLCHAIN_ROOT}
      -DMAKE_ROOT=${MAKE_ROOT}
      -DQMK_KEYBOARD=${KEYBOARD_NAME}
      -DQMK_KEYBOARD_FOLDER=${KEYBOARD_FOLDER}
  )
endmacro(add_keyboard)