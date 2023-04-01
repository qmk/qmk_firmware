macro(add_qmk_executable_common target_name)

    file(READ ${CMAKE_SOURCE_DIR}/info.json JSON_STRING)

    string(JSON KEYBOARD_NAME GET ${JSON_STRING} keyboard_name)
    string(JSON MANUFACTURER GET ${JSON_STRING} manufacturer)
    string(JSON QMK_MCU GET ${JSON_STRING} processor)
    string(JSON VENDOR_ID GET ${JSON_STRING} usb vid)
    string(JSON PRODUCT_ID GET ${JSON_STRING} usb pid)
    string(JSON DEVICE_VER GET ${JSON_STRING} usb device_version)

    string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)"
       VERSION_MATCH ${DEVICE_VER})
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH ${CMAKE_MATCH_3})
    math(EXPR VERSION_C_EVAL "${VERSION_MAJOR} * 10000 + ${VERSION_MINOR} * 100 + ${VERSION_PATCH}" OUTPUT_FORMAT HEXADECIMAL)

    # include_directories(${QMK_ROOT}/quantum)
    # include_directories(${QMK_ROOT}/quantum/logging)
    # include_directories(${QMK_ROOT}/quantum/keymap_extras)
    # include_directories(${QMK_ROOT}/quantum/process_keycode)
    # include_directories(${QMK_ROOT}/quantum/sequencer)
    # include_directories(${QMK_ROOT}/quantum/bootmagic)
    # include_directories(${QMK_ROOT}/platforms)
    include_directories(${CMAKE_SOURCE_DIR})

    add_compile_options(
        -include ${CMAKE_SOURCE_DIR}/config.h
        -mmcu=${QMK_MCU}
    )

    add_link_options(
        -mmcu=${QMK_MCU}
    )

    add_compile_definitions(
        QMK_KEYBOARD_H="${target_name}.h"
        KEYMAP_C="${CMAKE_SOURCE_DIR}/keymaps/default/keymap.c"
        MATRIX_ROWS=6
        MATRIX_COLS=15
        VENDOR_ID=${VENDOR_ID}
        PRODUCT_ID=${PRODUCT_ID}
        DEVICE_VER=${VERSION_C_EVAL}
        MANUFACTURER="${MANUFACTURER}"
        PRODUCT="${KEYBOARD_NAME}"
    )

    # add_library(qmk)

    add_subdirectory(${QMK_ROOT}/quantum quantum)
    add_subdirectory(${QMK_ROOT}/platforms platforms)
    add_subdirectory(${QMK_ROOT}/tmk_core/protocol tmk_core/protocol)
endmacro(add_qmk_executable_common)