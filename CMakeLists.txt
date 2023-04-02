cmake_minimum_required(VERSION 3.3)

macro(add_qmk_executable _)
endmacro(add_qmk_executable)

if(NOT DEFINED QMK_KEYBOARD)

project(qmk_firmware)

include(ExternalProject)

macro(add_keyboard KEYBOARD_CMAKE)
  get_filename_component(KEYBOARD_FULL_DIRECTORY "${KEYBOARD_CMAKE}" DIRECTORY)
  file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FULL_DIRECTORY}")
  string(REPLACE "/" "." KEYBOARD_NAME ${KEYBOARD_FOLDER})
  ExternalProject_Add(${KEYBOARD_NAME}
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    TMP_DIR ${CMAKE_SOURCE_DIR}/build
    INSTALL_COMMAND cmake -E echo "No install needed"
    CMAKE_GENERATOR "Unix Makefiles"
    CMAKE_ARGS 
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/platforms/avr/toolchain.cmake
      -DQMK_KEYBOARD=${KEYBOARD_NAME}
      -DQMK_KEYBOARD_FOLDER=${KEYBOARD_FOLDER}
  )
endmacro(add_keyboard)

if(DEFINED QMK_KEYBOARD_FOLDER)
  add_keyboard(${CMAKE_SOURCE_DIR}/keyboards/${QMK_KEYBOARD_FOLDER}/CMakeFiles.txt)
endif()

file(GLOB_RECURSE KEYBOARDS keyboards/**/CMakeLists.txt)

foreach(KEYBOARD_CMAKE ${KEYBOARDS})
  add_keyboard(${KEYBOARD_CMAKE})
endforeach()

else()

set(QMK_KEYBOARD_CURRENT_FOLDER ${QMK_KEYBOARD_FOLDER})
set(QMK_KEYBOARD_FOLDERS)
set(QMK_KEYBOARD_FOLDER_PARTS)
while(NOT ${QMK_KEYBOARD_CURRENT_FOLDER} STREQUAL "")
  get_filename_component(QMK_KEYBOARD_CURRENT_PART ${QMK_KEYBOARD_CURRENT_FOLDER} NAME)
  list(PREPEND QMK_KEYBOARD_FOLDER_PARTS ${QMK_KEYBOARD_CURRENT_PART})
  list(PREPEND QMK_KEYBOARD_FOLDERS ${QMK_KEYBOARD_CURRENT_FOLDER})
  get_filename_component(QMK_KEYBOARD_CURRENT_FOLDER ${QMK_KEYBOARD_CURRENT_FOLDER} DIRECTORY)
endwhile()

file(READ keyboards/${QMK_KEYBOARD_FOLDER}/info.json JSON_STRING)
string(JSON KEYBOARD_NAME GET ${JSON_STRING} keyboard_name)
string(JSON MANUFACTURER GET ${JSON_STRING} manufacturer)
string(JSON QMK_MCU GET ${JSON_STRING} processor)
string(JSON VENDOR_ID GET ${JSON_STRING} usb vid)
string(JSON PRODUCT_ID GET ${JSON_STRING} usb pid)
string(JSON DEVICE_VER GET ${JSON_STRING} usb device_version)

foreach(FOLDER ${QMK_KEYBOARD_FOLDERS})
  include_directories(${CMAKE_SOURCE_DIR}/keyboards/${FOLDER})
  if(EXISTS ${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/config.h)
    list(APPEND QMK_KEYBOARD_CONFIG_HS "${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/config.h")
  endif()
  if(EXISTS ${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/keymaps/default/keymap.c)
    list(APPEND QMK_KEYBOARD_KEYMAPS "${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/keymaps/default/keymap.c")
  endif()
  # not sure if merging is needed, since info.json is required iirc
  # if(EXISTS keyboards/${FOLDER}/info.json)
  #   file(READ keyboards/${FOLDER}/info.json JSON_STRING)
  #   string(JSON KEYBOARD_NAME GET ${JSON_STRING} keyboard_name)
  #   string(JSON MANUFACTURER GET ${JSON_STRING} manufacturer)
  #   string(JSON QMK_MCU GET ${JSON_STRING} processor)
  #   string(JSON VENDOR_ID GET ${JSON_STRING} usb vid)
  #   string(JSON PRODUCT_ID GET ${JSON_STRING} usb pid)
  #   string(JSON DEVICE_VER GET ${JSON_STRING} usb device_version)
  # endif()
endforeach()

if(NOT DEFINED QMK_KEYBOARD_KEYMAPS)
  message(FATAL_ERROR "Keymap not found")
endif()

list(GET QMK_KEYBOARD_FOLDERS 0 QMK_KEYBOARD_BASE_FOLDER)
list(GET QMK_KEYBOARD_KEYMAPS 0 QMK_KEYBOARD_KEYMAP)
list(GET QMK_KEYBOARD_FOLDER_PARTS -1 QMK_KEYBOARD_FOLDER_LAST_PART)

project(${QMK_KEYBOARD} 
  LANGUAGES C CXX ASM 
  VERSION ${DEVICE_VER})

string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)" VERSION_MATCH ${DEVICE_VER})
set(VERSION_MAJOR ${CMAKE_MATCH_1})
set(VERSION_MINOR ${CMAKE_MATCH_2})
set(VERSION_PATCH ${CMAKE_MATCH_3})
math(EXPR VERSION_C_EVAL "${VERSION_MAJOR} * 10000 + ${VERSION_MINOR} * 100 + ${VERSION_PATCH}" OUTPUT_FORMAT HEXADECIMAL)


add_compile_options(
    -include ${QMK_KEYBOARD_CONFIG_HS}
    -mmcu=${QMK_MCU}
)

add_link_options(
    -mmcu=${QMK_MCU}
)

add_compile_definitions(
    QMK_KEYBOARD_H="${QMK_KEYBOARD_FOLDER_LAST_PART}.h"
    KEYMAP_C="${QMK_KEYBOARD_KEYMAP}"
    MATRIX_ROWS=6
    MATRIX_COLS=15
    VENDOR_ID=${VENDOR_ID}
    PRODUCT_ID=${PRODUCT_ID}
    DEVICE_VER=${VERSION_C_EVAL}
    MANUFACTURER="${MANUFACTURER}"
    PRODUCT="${KEYBOARD_NAME}"
)

add_subdirectory(quantum)
add_subdirectory(platforms)
add_subdirectory(tmk_core/protocol)

# option(OLED_ENABLE "" TRUE)
# if(${OLED_ENABLE})
#     target_sources(quantum PUBLIC 
#       ${CMAKE_SOURCE_DIR}/drivers/oled/ssd1306_sh1106.c 
#       ${CMAKE_SOURCE_DIR}/platforms/${CMAKE_SYSTEM_PROCESSOR}/drivers/i2c_master.c)
#     add_compile_definitions(OLED_ENABLE)
#     target_include_directories(quantum PUBLIC ${CMAKE_SOURCE_DIR}/drivers)
#     target_include_directories(quantum PUBLIC ${CMAKE_SOURCE_DIR}/drivers/oled)
#     target_include_directories(quantum PUBLIC ${CMAKE_SOURCE_DIR}/platforms/${CMAKE_SYSTEM_PROCESSOR}/drivers)
# endif()

if(EXISTS keyboards/${QMK_KEYBOARD_FOLDER}/CMakeLists.txt)
  add_subdirectory(keyboards/${QMK_KEYBOARD_FOLDER})
else()
  file(GLOB KEYBOARD_SRC "keyboards/${QMK_KEYBOARD_FOLDER}/*.c")
  add_qmk_executable(${QMK_KEYBOARD} ${KEYBOARD_SRC})
endif()

endif()