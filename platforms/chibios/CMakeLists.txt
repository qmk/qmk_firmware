find_package(chibios REQUIRED)

target_link_options(qmk PUBLIC
    -mcpu=${QMK_MCU}
    -mthumb
    -mno-thumb-interwork
    -mno-unaligned-access
)

target_compile_definitions(qmk PUBLIC
    MCU_${MCU_FAMILY}
    THUMB_PRESENT
    THUMB_NO_INTERWORKING
    PLATFORM_SUPPORTS_SYNCHRONIZATION
    PORT_IGNORE_GCC_VERSION_CHECK=1
)

if(NOT ${USE_FPU})
    target_compile_options(qmk PUBLIC
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        -fsingle-precision-constant
    )
    target_compile_definitions(qmk PUBLIC
        CORTEX_USE_FPU=TRUE
    )
else()
    target_compile_definitions(qmk PUBLIC
        CORTEX_USE_FPU=FALSE
    )
endif()

# add_library(platforms_chibios)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/boards/common/configs)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}/configs)
# target_link_libraries(platforms_chibios ${QMK_TARGET})