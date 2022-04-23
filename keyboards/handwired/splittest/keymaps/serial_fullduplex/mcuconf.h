#pragma once

#include_next <mcuconf.h>

#if defined(BLUEPILL)
    #if defined(USE_SDI1_ON_STANDARD_ROLE_PINS) || defined(USE_SDI1_ON_ALTERNATE_ROLE_PINS)
        #undef STM32_SERIAL_USE_USART1
        #define STM32_SERIAL_USE_USART1 TRUE
    #elif defined(USE_SDI2)
        #undef STM32_SERIAL_USE_USART2
        #define STM32_SERIAL_USE_USART2 TRUE
    #else
        #error "splittest serial_fullduplex keymap is missing a configuration (USE_SDI1_ON_STANDARD_ROLE_PINS, USE_SDI1_ON_ALTERNATE_ROLE_PINS, USE_SDI2)"
    #endif
#endif
