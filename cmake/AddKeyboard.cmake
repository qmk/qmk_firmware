include(ResolveKeyboard)
include(ValidateJson)
include(ResolveToolchain)

macro(add_keyboard KEYBOARD_FOLDER KEYMAP_FOLDER)  
  # not entirely sure why this is necessary
  # set(TEMP_PATH ${KEYBOARD_FOLDER})
  # cmake_path(IS_RELATIVE TEMP_PATH IS_KEYBOARD_FOLDER_RELATIVE)
  # if(${IS_KEYBOARD_FOLDER_RELATIVE})
  #   set(KEYBOARD_FOLDER_ABS ${CMAKE_SOURCE_DIR}/keyboards/${KEYBOARD_FOLDER})
  #   if(NOT EXISTS ${KEYBOARD_FOLDER_ABS})
  #     # message(FATAL_ERROR "Keyboard does not exist in QMK - try using an absolute path to the keyboard folder")
  #     resolve_keyboard(${KEYBOARD_FOLDER} KEYBOARD_FOLDER_ABS)
  #   endif()
  # else()
  #   set(KEYBOARD_FOLDER_ABS ${KEYBOARD_FOLDER})
  #   if(NOT EXISTS ${KEYBOARD_FOLDER_ABS})
  #     message(FATAL_ERROR "Absolute path to keyboard does not exist")
  #   endif()
  # endif()
 
  resolve_keyboard(${KEYBOARD_FOLDER} KEYBOARD_FOLDER_ABS)

  set(TEMP_PATH ${KEYBOARD_FOLDER})
  cmake_path(IS_RELATIVE TEMP_PATH IS_KEYBOARD_FOLDER_RELATIVE)
  
  set(TEMP_PATH ${KEYMAP_FOLDER})
  cmake_path(IS_RELATIVE TEMP_PATH IS_KEYMAP_FOLDER_RELATIVE)
  if(${IS_KEYMAP_FOLDER_RELATIVE})
    set(KEYMAP_NAME ${KEYMAP_FOLDER})
  else()
    if(WIN32)
      set(KEYMAP_NAME $ENV{USERNAME})
    else()
      set(KEYMAP_NAME $ENV{USE})
    endif()
  endif()

  # find the right toolchain

  # not sure we need to validate here
  validate_json(${KEYBOARD_FOLDER_ABS}/info.json keyboard JSON_STRING)

  string(JSON PROCESSOR GET ${JSON_STRING} processor)
  resolve_toolchain(${PROCESSOR} TOOLCHAIN)

  string(JSON KEYBOARD_NAME GET ${JSON_STRING} keyboard_name)
  if(${IS_KEYBOARD_FOLDER_RELATIVE})
    string(MAKE_C_IDENTIFIER ${KEYBOARD_FOLDER} KEYBOARD_SLUG)
  else()
    string(MAKE_C_IDENTIFIER ${KEYBOARD_NAME} KEYBOARD_SLUG)
  endif()
  string(JSON MANUFACTURER GET ${JSON_STRING} manufacturer)
  set(TARGET_NAME "${KEYBOARD_SLUG}_${KEYMAP_NAME}")
  ExternalProject_Add(${TARGET_NAME}
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    # PREFIX ${CMAKE_SOURCE_DIR}/build/keyboards/${KEYBOARD_FOLDER}
    TMP_DIR ${CMAKE_SOURCE_DIR}/build/tmp
    DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/build/download
    BINARY_DIR ${CMAKE_SOURCE_DIR}/build/keyboards/${TARGET_NAME}
    STAMP_DIR ${CMAKE_SOURCE_DIR}/build/stamp
    LOG_DIR ${CMAKE_SOURCE_DIR}/build/log
    INSTALL_DIR ${CMAKE_SOURCE_DIR}/build/install
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/${TARGET_NAME}${QMK_EXTENSION} ${CMAKE_SOURCE_DIR}/${TARGET_NAME}${QMK_EXTENSION}
    # this seems to work well for all systems so far - not sure if it'd be useful to customize
    CMAKE_GENERATOR "Unix Makefiles"
    CMAKE_ARGS 
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/cmake/toolchains/${TOOLCHAIN}.cmake
      -DQMK_KEYBOARD=${KEYBOARD_SLUG}
      -DQMK_KEYBOARD_FOLDER=${KEYBOARD_FOLDER}
      -DQMK_KEYMAP_FOLDER=${KEYMAP_FOLDER}
      -DTARGET_NAME=${TARGET_NAME}
  )
  ExternalProject_Add_Step(${TARGET_NAME} copy_compile_commands
    DEPENDEES configure
    DEPENDERS build
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/keyboards/${TARGET_NAME}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    # BYPRODUCTS ${CMAKE_SOURCE_DIR}/compile_commands.json
    ALWAYS TRUE
  )
  
# file(APPEND "${CMAKE_SOURCE_DIR}/build/targets" "${TARGET_NAME}|${KEYBOARD_NAME} with ${KEYMAP_FOLDER}|${KEYBOARD_FOLDER}|Made by: ${MANUFACTURER}\n")
endmacro(add_keyboard)
