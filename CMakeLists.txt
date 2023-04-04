cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(UpdateSubmodule)
include(ResolveKeyboard)
include(ValidateJSON)

set(QMK_KEYBOARDS_FOLDER "${CMAKE_SOURCE_DIR}/keyboards")

function (_get_all_cmake_targets out_var current_dir)
    get_property(targets DIRECTORY ${current_dir} PROPERTY BUILDSYSTEM_TARGETS)
    get_property(subdirs DIRECTORY ${current_dir} PROPERTY SUBDIRECTORIES)

    foreach(subdir ${subdirs})
        _get_all_cmake_targets(subdir_targets ${subdir})
        list(APPEND targets ${subdir_targets})
    endforeach()

    set(${out_var} ${targets} PARENT_SCOPE)
endfunction()

if(NOT DEFINED QMK_KEYBOARD)

# configure step - populate targets

project(qmk_firmware)

add_subdirectory(keyboards)

else()

# build step

if(NOT DEFINED QMK_KEYMAP_FOLDER)
  set(QMK_KEYMAP_FOLDER "default")
endif()

resolve_keyboard(${QMK_KEYBOARD_FOLDER} QMK_KEYBOARD_FOLDER_ABS)
cmake_path(IS_PREFIX QMK_KEYBOARDS_FOLDER "${QMK_KEYBOARD_FOLDER_ABS}" IS_KEYBOARDS_FOLDER)
resolve_config_h(${QMK_KEYBOARD_FOLDER_ABS} QMK_KEYBOARD_CONFIG_H)
resolve_keyboard_h(${QMK_KEYBOARD_FOLDER_ABS} QMK_KEYBOARD_H)
resolve_keymap_c(${QMK_KEYBOARD_FOLDER_ABS} ${QMK_KEYMAP_FOLDER} QMK_KEYMAP_C)

message(STATUS "config.h: ${QMK_KEYBOARD_CONFIG_H}")
message(STATUS "keyboard.h: ${QMK_KEYBOARD_H}")
message(STATUS "keymap.c: ${QMK_KEYMAP_C}")

validate_json(${QMK_KEYBOARD_FOLDER_ABS}/info.json keyboard QMK_KEYBOARD_INFO_JSON_STRING)

string(JSON KEYBOARD_NAME GET ${QMK_KEYBOARD_INFO_JSON_STRING} keyboard_name)
string(JSON MANUFACTURER GET ${QMK_KEYBOARD_INFO_JSON_STRING} manufacturer)
string(JSON URL GET ${QMK_KEYBOARD_INFO_JSON_STRING} url)
string(JSON QMK_MCU GET ${QMK_KEYBOARD_INFO_JSON_STRING} processor)
string(JSON VENDOR_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb vid)
string(JSON PRODUCT_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb pid)
string(JSON DEVICE_VER GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb device_version)

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
    -include ${QMK_KEYBOARD_CONFIG_H}
)

add_compile_definitions(
    QMK_KEYBOARD_H="${QMK_KEYBOARD_H}"
    KEYMAP_C="${QMK_KEYMAP_C}"
    MATRIX_ROWS=6
    MATRIX_COLS=15
    VENDOR_ID=${VENDOR_ID}
    PRODUCT_ID=${PRODUCT_ID}
    DEVICE_VER=${VERSION_C_EVAL}
    MANUFACTURER="${MANUFACTURER}"
    PRODUCT="${KEYBOARD_NAME}"
)

# if(EXISTS ${QMK_KEYBOARD_FOLDER_ABS}/CMakeLists.txt)
  # add_subdirectory(${QMK_KEYBOARD_FOLDER_ABS})
# else()
  file(GLOB KEYBOARD_SRC "${QMK_KEYBOARD_FOLDER_ABS}/*.c")
  list(REMOVE_ITEM KEYBOARD_SRC "${QMK_KEYBOARD_KEYMAP}")
  add_qmk_executable(${TARGET_NAME} ${KEYBOARD_SRC})
# endif()

add_library(qmk)

resolve_keyboard_includes(${QMK_KEYBOARD_FOLDER_ABS})

add_subdirectory(quantum)
add_subdirectory(platforms)
add_subdirectory(tmk_core/protocol)

include(features/oled)
include(features/backlight)

endif()