set(EEPROM_DRIVER "vendor" CACHE STRING "EEPROM driver")
set_property(CACHE EEPROM_DRIVER PROPERTY STRINGS vendor custom transient i2c spi wear_leveling legacy_stm32_flash)
set(WEAR_LEVELING_DRIVER "none" CACHE STRING "EEPROM wear-leveling driver")
set_property(CACHE WEAR_LEVELING_DRIVER PROPERTY STRINGS custom embedded_flash spi_flash rp2040_flash legacy)

target_compile_definitions(qmk PUBLIC
    EEPROM_ENABLE
)
target_include_directories(qmk PUBLIC
    platforms/${QMK_PLATFORM}/drivers/eeprom
    drivers/eeprom
    platforms/common
)

if(${EEPROM_DRIVER} STREQUAL "wear_leveling")
    target_compile_definitions(qmk PUBLIC 
        EEPROM_DRIVER
        EEPROM_WEAR_LEVELING
    )
    target_sources(qmk PUBLIC 
        drivers/eeprom/eeprom_driver.c
        drivers/eeprom/eeprom_wear_leveling.c
    )
elseif(${EEPROM_DRIVER} STREQUAL "vendor")
    target_compile_definitions(qmk PUBLIC 
        EEPROM_VENDOR
    )
    if(${QMK_PLATFORM} STREQUAL "chibios")
        if(${QMK_MCU} MATCHES "STM32F[1-9].*" OR ${QMK_MCU} MATCHES "WB32.*" OR ${QMK_MCU} MATCHES "GD32.*")
            target_compile_definitions(qmk PUBLIC 
                EEPROM_DRIVER
                EEPROM_WEAR_LEVELING
            )
            target_sources(qmk PUBLIC
                drivers/eeprom/eeprom_driver.c
                drivers/eeprom/eeprom_wear_leveling.c
            )
            set(WEAR_LEVELING_DRIVER "embedded_flash")
        endif()
    endif()
endif()

if(NOT ${WEAR_LEVELING_DRIVER} STREQUAL "none")
    set(FNV_ENABLE TRUE)
    target_compile_definitions(qmk PUBLIC 
        WEAR_LEVELING_ENABLE
    )
    target_include_directories(qmk PUBLIC
        platforms/${QMK_PLATFORM}/drivers/wear_leveling
        drivers/wear_leveling
        quantum/wear_leveling
    )
    target_sources(qmk PUBLIC quantum/wear_leveling/wear_leveling.c)

    if(${WEAR_LEVELING_DRIVER} STREQUAL "embedded_flash")
        target_compile_definitions(qmk PUBLIC 
            HAL_USE_EFL
            WEAR_LEVELING_EMBEDDED_FLASH
        )
        target_sources(qmk PUBLIC 
            platforms/${QMK_PLATFORM}/drivers/wear_leveling/wear_leveling_efl.c
        )
        # target_compile_options(qmk PUBLIC
            # -include ${CMAKE_SOURCE_DIR}/platforms/${QMK_PLATFORM}/drivers/wear_leveling/wear_leveling_efl_config.h
        # )
        target_precompile_headers(qmk PUBLIC
            ${CMAKE_SOURCE_DIR}/platforms/${QMK_PLATFORM}/drivers/wear_leveling/wear_leveling_efl_config.h
        )
    endif()
endif()
