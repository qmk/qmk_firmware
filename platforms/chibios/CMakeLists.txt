find_package(Chibios REQUIRED)

target_link_options(qmk PUBLIC
    -mcpu=${MCU}
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

# bootloader
if(${BOOTLOADER} STREQUAL "stm32-dfu")
    target_compile_definitions(qmk PUBLIC BOOTLOADER_STM32_DFU)
    set(BOOTLOADER_TYPE stm32_dfu)
endif()

target_sources(qmk PUBLIC
    syscall-fallbacks.c
    wait.c
    synchronization_util.c
    hardware_id.c
	platform.c
	suspend.c
	timer.c
	bootloaders/${BOOTLOADER_TYPE}.c
)

target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/boards/common/configs)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}/configs)

# mabye this should be in a different place
add_subdirectory(${CMAKE_SOURCE_DIR}/quantum/logging logging)