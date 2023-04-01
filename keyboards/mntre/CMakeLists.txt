cmake_minimum_required(VERSION 3.3)

project(mntre C CXX ASM)

add_qmk_executable(mntre
    mntre.c
)
# set(QMK_INFO_JSON ${CMAKE_CURRENT_SOURCE_DIR}/info.json PARENT_SCOPE)
# add_compile_definitions(QMK_KEYMAP_CONFIG_H="${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# avr_target_link_libraries(mntre qmk)