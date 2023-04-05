include(ParseMakefile)

set(MCU "cortex-m4")
set(ARMV 7)
set(MCU_FAMILY "STM32")
set(MCU_SERIES "STM32F3xx")
set(MCU_LDSCRIPT "STM32F303xC")
set(MCU_STARTUP "stm32f3xx")
set(BOARD "GENERIC_STM32_F303XC")
set(USE_FPU TRUE)
set(UF2_FAMILY "STM32F3")
set(STM32_BOOTLOADER_ADDRESS 0x1FFFD800)

set(MCU_PORT_NAME ${MCU_FAMILY})
set(MCU_ARCH ${MCU})
set(CHIBIOS_PORT "ARMv${ARMV}-M")
set(PLATFORM_NAME platform)

set(CHIBIOS ${CMAKE_SOURCE_DIR}/lib/chibios)
set(CHIBIOS_CONTRIB ${CMAKE_SOURCE_DIR}/lib/chibios-contrib)
set(EEPROM_DRIVER "wear_leveling" CACHE STRING "" FORCE)

# target_compile_definitions(qmk PUBLIC
    # __ARM_ARCH_7M__
    # STM32F303xC
# )

# F3 sources
set(CHIBIOS_PORT_SRCS
    # RT
    chcore.c
    chcoreasm.S
)
foreach(SRC_FILE ${CHIBIOS_PORT_SRCS})
    set(CHIBIOS_F3_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(CHIBIOS_F3_SRC_FILE ${SRC_FILE}
        PATHS 
            ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC
            ${CHIBIOS}/os/common/ports/ARMv7-M
        CMAKE_FIND_ROOT_PATH_BOTH
    )

    target_sources(qmk PUBLIC ${CHIBIOS_F3_SRC_FILE})
endforeach()

target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/common/ports/ARMv7-M
    ${CHIBIOS}/os/hal/boards/ST_STM32F3_DISCOVERY
)

# F3 HAL specific
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/common/ARMCMx
    ${CHIBIOS}/os/hal/include
    ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx

    ${CHIBIOS}/os/common/portability/GCC
    ${CHIBIOS}/os/common/ports/ARM-common
    ${CHIBIOS}/os/common/ports/ARMv7-M
    ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC
    ${CHIBIOS}/os/common/startup/ARMCMx/devices/STM32F3xx
    ${CHIBIOS}/os/common/ext/ARM/CMSIS/Core/Include
    ${CHIBIOS}/os/common/ext/ST/STM32F3xx

    ${CHIBIOS}/os/hal/ports/STM32/LLD/ADCv3
    ${CHIBIOS}/os/hal/ports/STM32/LLD/CANv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/DACv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/DMAv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/GPIOv2
    ${CHIBIOS}/os/hal/ports/STM32/LLD/I2Cv2
    ${CHIBIOS}/os/hal/ports/STM32/LLD/RTCv2
    # ${CHIBIOS}/os/hal/ports/STM32/LLD/SDIOv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/SPIv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/SYSTICKv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1
    # ${CHIBIOS}/os/hal/ports/STM32/LLD/USART
    ${CHIBIOS}/os/hal/ports/STM32/LLD/USARTv2
    ${CHIBIOS}/os/hal/ports/STM32/LLD/USBv1
    ${CHIBIOS}/os/hal/ports/STM32/LLD/xWDGv1
)

# source files for ChibiOS HAL
set(CHIBIOS_HAL_SRCS

    # startup code
    crt1.c
    vectors.S
    crt0_v7m.S

    nvic.c
    stm32_isr.c

    # HAL-OSAL files
    hal.c
    hal_st.c
    
    hal_buffers.c
    hal_queues.c
    hal_flash.c
    hal_mmcsd.c
    
    hal_adc.c
    hal_can.c
    # hal_crypto.c
    hal_dac.c
    hal_efl.c
    hal_gpt.c
    hal_i2c.c
    hal_i2s.c
    hal_icu.c
    hal_mac.c
    hal_mmc_spi.c
    hal_pal.c
    hal_pwm.c
    hal_rtc.c
    hal_sdc.c
    hal_serial.c
    hal_serial_usb.c
    hal_sio.c
    hal_spi.c
    hal_trng.c
    hal_uart.c
    hal_usb.c
    hal_wdg.c
    hal_wspi.c

    # LLD HAL files
    hal_lld.c

    hal_adc_lld.c
    hal_can_lld.c
    hal_crypto_lld.c
    hal_dac_lld.c
    stm32_dma.c
    stm32_exti.c
    hal_pal_lld.c
    hal_i2c_lld.c
    hal_mac_lld.c
    hal_usb_lld.c
    hal_wspi_lld.c 
    hal_trng_lld.c
    hal_rtc_lld.c
    hal_sdc_lld.c

    hal_i2s_lld.c
    hal_spi_v2_lld.c

    hal_st_lld.c
    hal_gpt_lld.c
    hal_icu_lld.c
    hal_pwm_lld.c

    hal_serial_lld.c
    hal_uart_lld.c

    hal_wdg_lld.c

    # OSAL 
    osal.c

    board.c
)

foreach(SRC_FILE ${CHIBIOS_HAL_SRCS})

    set(CHIBIOS_HAL_SRC_FILE SRC_FILE -NOTFOUND)

    find_file(CHIBIOS_HAL_SRC_FILE ${SRC_FILE}
        PATHS 

            ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC
            ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC

            ${CHIBIOS}/os/hal/src
            ${CHIBIOS}/os/hal/ports/common/ARMCMx

            ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx

            ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx
            ${CHIBIOS}/os/hal/ports/STM32/LLD/ADCv3
            ${CHIBIOS}/os/hal/ports/STM32/LLD/CANv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/DACv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/DMAv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/GPIOv2
            ${CHIBIOS}/os/hal/ports/STM32/LLD/I2Cv2
            ${CHIBIOS}/os/hal/ports/STM32/LLD/RTCv2
            ${CHIBIOS}/os/hal/ports/STM32/LLD/SPIv2
            ${CHIBIOS}/os/hal/ports/STM32/LLD/SYSTICKv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/USARTv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/USBv1
            ${CHIBIOS}/os/hal/ports/STM32/LLD/xWDGv1

            # ${OSHAL_PATH}
            
            # ${CHIBIOS_BOARD_DEFINITIONS_PATH}

        CMAKE_FIND_ROOT_PATH_BOTH
    )
    if(EXISTS "${CHIBIOS_HAL_SRC_FILE}")
        target_sources(qmk PUBLIC ${CHIBIOS_HAL_SRC_FILE})
    endif()
endforeach()

# chibios
target_include_directories(qmk PUBLIC
    # ${CHIBIOS}/os/hal/include
    # ${CHIBIOS}/os/hal/osal/sb
    # ${CHIBIOS}/os/common/portability/GCC
    # ${CHIBIOS}/os/sb/user
    # ${CHIBIOS}/os/sb/common

    ${CHIBIOS}/os
    ${CHIBIOS}/os/license
    ${CHIBIOS}/os/hal/ports/common/ARMCMx
    ${CHIBIOS}/os/hal/include
    ${CHIBIOS}/os/hal/osal/rt-nil
    ${CHIBIOS}/os/oslib/include
    ${CHIBIOS}/os/rt/include
    ${CHIBIOS}/os/hal/ports/STM32/${MCU_SERIES}
    ${CHIBIOS}/os/common/ports/ARMv7-M
    ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC
    ${CHIBIOS}/os/common/abstractions/cmsis_os
    ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC
    ${CHIBIOS}/os/common/ext/CMSIS/include
    ${CHIBIOS}/os/common/ext/CMSIS/ST/${MCU_SERIES}
)