set(EEPROM_DRIVER "vendor" CACHE STRING "EEPROM driver")
set_property(CACHE EEPROM_DRIVER PROPERTY STRINGS vendor custom transient i2c spi wear_leveling legacy_stm32_flash)
set(WEAR_LEVELING_DRIVER "none" CACHE STRING "EEPROM wear-leveling driver")
set_property(CACHE WEAR_LEVELING_DRIVER PROPERTY STRINGS custom embedded_flash spi_flash rp2040_flash legacy)

if(${EEPROM_DRIVER} STREQUAL "wear_leveling")
    target_compile_definitions(qmk PUBLIC 
        EEPROM_DRIVER
        EEPROM_WEAR_LEVELING
    )
    target_sources(qmk PUBLIC 
        drivers/eeprom/eeprom_driver.c
        drivers/eeprom/eeprom_wear_leveling.c
    )
    target_include_directories(qmk PUBLIC drivers/eeprom)
elseif(${EEPROM_DRIVER} STREQUAL "vendor")
    target_compile_definitions(qmk PUBLIC 
        EEPROM_VENDOR
    )
    if(${QMK_PLATFORM} STREQUAL "chibios")
        if(${QMK_MCU} MATHCES "STM32F.*")
            target_compile_definitions(qmk PUBLIC 
                EEPROM_DRIVER
                EEPROM_WEAR_LEVELING
            )
            target_sources(qmk PUBLIC
                drivers/eeprom/eeprom_driver.c
                drivers/eeprom/eeprom_wear_leveling.c
            )
            set(WEAR_LEVELING_DRIVER "embedded_flash" FORCE)
        endif()
    endif()
endif()

if(NOT ${WEAR_LEVELING_DRIVER} STREQUAL "none")
    target_compile_definitions(qmk PUBLIC 
        WEAR_LEVELING_ENABLE
        WEAR_LEVELING_EMBEDDED_FLASH
    )
    target_include_directories(qmk PUBLIC
        platforms/${QMK_PLATFORM}/drivers/wear_leveling
        drivers/wear_leveling
        quantum/wear_leveling
    )
    target_sources(qmk PUBLIC wear_leveling.c)

    if(NOT ${WEAR_LEVELING_DRIVER} STREQUAL "embedded_flash")
        target_compile_definitions(qmk PUBLIC 
            HAL_USE_EFL
        )
        target_sources(qmk PUBLIC wear_leveling_efl.c)
        # post config.h platforms/${QMK_PLATFORM}/drivers/wear_leveling/wear_leveling_efl_config.h
    endif()
endif()
