add_link_options(
    -mcpu=${QMK_MCU}
)
add_library(platforms_chibios)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(platforms_chibios ${QMK_TARGET})