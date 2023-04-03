cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(UpdateSubmodule)

# early declaration of macro defined in toolchain
macro(add_qmk_executable _)
endmacro(add_qmk_executable)

if(NOT DEFINED QMK_KEYBOARD)

# configure step - populate targets

project(qmk_firmware)

add_subdirectory(keyboards)

else()

# build step

set(QMK_KEYBOARD_CURRENT_FOLDER ${QMK_KEYBOARD_FOLDER})
set(QMK_KEYBOARD_FOLDERS)
set(QMK_KEYBOARD_FOLDER_PARTS)
while(NOT ${QMK_KEYBOARD_CURRENT_FOLDER} STREQUAL "")
  get_filename_component(QMK_KEYBOARD_CURRENT_PART ${QMK_KEYBOARD_CURRENT_FOLDER} NAME)
  list(PREPEND QMK_KEYBOARD_FOLDER_PARTS ${QMK_KEYBOARD_CURRENT_PART})
  list(PREPEND QMK_KEYBOARD_FOLDERS ${QMK_KEYBOARD_CURRENT_FOLDER})
  get_filename_component(QMK_KEYBOARD_CURRENT_FOLDER ${QMK_KEYBOARD_CURRENT_FOLDER} DIRECTORY)
endwhile()

# would be nice to also do validation here
file(READ keyboards/${QMK_KEYBOARD_FOLDER}/info.json QMK_KEYBOARD_INFO_JSON_STRING)
string(JSON KEYBOARD_NAME GET ${QMK_KEYBOARD_INFO_JSON_STRING} keyboard_name)
string(JSON MANUFACTURER GET ${QMK_KEYBOARD_INFO_JSON_STRING} manufacturer)
string(JSON URL GET ${QMK_KEYBOARD_INFO_JSON_STRING} url)
string(JSON QMK_MCU GET ${QMK_KEYBOARD_INFO_JSON_STRING} processor)
string(JSON VENDOR_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb vid)
string(JSON PRODUCT_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb pid)
string(JSON DEVICE_VER GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb device_version)

if(NOT DEFINED QMK_KEYMAP_FOLDER)
  set(QMK_KEYMAP_FOLDER "default")
endif()

set(TEMP_PATH ${QMK_KEYMAP_FOLDER})
cmake_path(IS_RELATIVE TEMP_PATH IS_KEYMAP_FOLDER_RELATIVE)

if(NOT ${IS_KEYMAP_FOLDER_RELATIVE})
  if(EXISTS "${QMK_KEYMAP_FOLDER}/keymap.c")
    set(QMK_KEYBOARD_KEYMAP "${QMK_KEYMAP_FOLEDR}/keymap.c")
  else()
    message(FATAL_ERROR "Could not find keymap.c in keymap folder")
  endif()
endif()

foreach(FOLDER ${QMK_KEYBOARD_FOLDERS})
  include_directories(${CMAKE_SOURCE_DIR}/keyboards/${FOLDER})
  # assuming every keyboard has a config at some level
  if(EXISTS ${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/config.h)
    list(APPEND QMK_KEYBOARD_CONFIG_HS "${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/config.h")
  endif()
  if(${IS_KEYMAP_FOLDER_RELATIVE})
    # assuming every keyboard has a default/keymap.c at some level
    if(EXISTS ${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/keymaps/${QMK_KEYMAP_FOLDER}/keymap.c)
      list(APPEND QMK_KEYBOARD_KEYMAPS "${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/keymaps/${QMK_KEYMAP_FOLDER}/keymap.c")
    endif()
  endif()
  get_filename_component(LAST_PART ${FOLDER} NAME)
  # assuming every keyboard has a header.h at some level
  if(EXISTS ${CMAKE_SOURCE_DIR}/keyboards/${FOLDER}/${LAST_PART}.h)
    # use just the filename, since the folder is already in our include path (maybe it should only be the base keyboard folder?)
    list(APPEND QMK_KEYBOARD_HEADERS "${LAST_PART}.h")
  endif()
  # not sure if merging is needed, since info.json is required per level? iirc
  # if(EXISTS keyboards/${FOLDER}/info.json)
  #   file(READ keyboards/${FOLDER}/info.json QMK_KEYBOARD_INFO_JSON_STRING)
  #   string(JSON KEYBOARD_NAME GET ${QMK_KEYBOARD_INFO_JSON_STRING} keyboard_name)
  #   string(JSON MANUFACTURER GET ${QMK_KEYBOARD_INFO_JSON_STRING} manufacturer)
  #   string(JSON QMK_MCU GET ${QMK_KEYBOARD_INFO_JSON_STRING} processor)
  #   string(JSON VENDOR_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb vid)
  #   string(JSON PRODUCT_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb pid)
  #   string(JSON DEVICE_VER GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb device_version)
  # endif()
endforeach()

if(${IS_KEYMAP_FOLDER_RELATIVE})
  if(NOT DEFINED QMK_KEYBOARD_KEYMAPS)
    message(FATAL_ERROR "Keymap not found")
  endif()
  list(GET QMK_KEYBOARD_KEYMAPS 0 QMK_KEYBOARD_KEYMAP)
endif()

if(NOT DEFINED QMK_KEYBOARD_HEADERS)
  message(FATAL_ERROR "Header not found")
endif()

# list(GET QMK_KEYBOARD_FOLDERS 0 QMK_KEYBOARD_BASE_FOLDER)
list(GET QMK_KEYBOARD_HEADERS -1 QMK_KEYBOARD_HEADER)

project(${QMK_KEYBOARD} 
  LANGUAGES C CXX ASM 
  HOMEPAGE_URL ${URL}
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
    QMK_KEYBOARD_H="${QMK_KEYBOARD_HEADER}"
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

include(features/oled)
include(features/backlight)

if(EXISTS keyboards/${QMK_KEYBOARD_FOLDER}/CMakeLists.txt)
  add_subdirectory(keyboards/${QMK_KEYBOARD_FOLDER})
else()
  file(GLOB KEYBOARD_SRC "keyboards/${QMK_KEYBOARD_FOLDER}/*.c")
  add_qmk_executable(${QMK_KEYBOARD} ${KEYBOARD_SRC})
endif()

endif()