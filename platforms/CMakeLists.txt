add_library(platforms suspend.c synchronization_util.c timer.c)
target_include_directories(platforms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(platforms PUBLIC quantum)

add_subdirectory(${QMK_PLATFORM})