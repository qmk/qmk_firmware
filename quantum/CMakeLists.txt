target_sources(qmk PUBLIC
    main.c 
    keymap_introspection.c
    quantum.c
    bitwise.c
    led.c
    action.c
    action_layer.c
    action_tapping.c
    action_util.c
    eeconfig.c
    keyboard.c
    keymap_common.c
    keycode_config.c
    sync_timer.c
    logging/debug.c
    logging/sendchar.c
    matrix_common.c
    matrix.c
    debounce/sym_defer_g.c
    bootmagic/magic.c
)

target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/logging)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/keymap_extras)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/process_keycode)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sequencer)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bootmagic)

# target_link_libraries(quantum ${QMK_TARGET})
# target_link_libraries(quantum platforms)
# target_link_libraries(quantum platforms_${QMK_PLATFORM})
# target_link_libraries(quantum tmk_core_protocol)
# target_link_libraries(quantum tmk_core_protocol_${QMK_PROTOCOL})

# if no printf
target_sources(qmk PUBLIC ${CMAKE_SOURCE_DIR}/lib/printf/src/printf/printf.c)
target_include_directories(qmk PUBLIC ${CMAKE_SOURCE_DIR}/lib/printf/src/printf)