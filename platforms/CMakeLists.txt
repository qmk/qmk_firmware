target_sources(qmk PUBLIC suspend.c synchronization_util.c timer.c)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(platforms ${QMK_TARGET})
# target_link_libraries(platforms quantum)

add_subdirectory(${QMK_PLATFORM})