
#if defined(SPLIT_BITBANG)

    #define SOFT_SERIAL_PIN B8

#elif defined(SPLIT_SERIAL_HALFDUPLEX)

    #if defined(USE_SDI1_ON_STANDARD_ROLE_PINS)
        #define SOFT_SERIAL_PIN A9
    #elif defined(USE_SDI1_ON_ALTERNATE_ROLE_PINS)
        #define SOFT_SERIAL_PIN B6
        #define USART1_REMAP // Remap USART TX and RX pins on STM32F103 MCUs
    #elif defined(USE_SDI2)
        #define SOFT_SERIAL_PIN A2
        #define SERIAL_USART_DRIVER SD2 // USART driver of TX and RX pin. default: SD1
    #else
        #error "splittest serial_halfduplex keymap is missing a configuration (USE_SDI1_ON_STANDARD_ROLE_PINS, USE_SDI1_ON_ALTERNATE_ROLE_PINS, USE_SDI2)"
    #endif

#elif defined(SPLIT_SERIAL_FULLDUPLEX)

    #define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.

    #if defined(USE_SDI1_ON_STANDARD_ROLE_PINS)
        #define SOFT_SERIAL_PIN A9
        #define SERIAL_USART_RX_PIN A10 // USART RX pin
    #elif defined(USE_SDI1_ON_ALTERNATE_ROLE_PINS)
        #define SOFT_SERIAL_PIN B6
        #define SERIAL_USART_RX_PIN B7 // USART RX pin
        #define USART1_REMAP           // Remap USART TX and RX pins on STM32F103 MCUs
    #elif defined(USE_SDI2)
        #define SOFT_SERIAL_PIN A2
        #define SERIAL_USART_RX_PIN A3  // USART RX pin
        #define SERIAL_USART_DRIVER SD2 // USART driver of TX and RX pin. default: SD1
    #else
        #error "splittest serial_fullduplex keymap is missing a configuration (USE_SDI1_ON_STANDARD_ROLE_PINS, USE_SDI1_ON_ALTERNATE_ROLE_PINS, USE_SDI2)"
    #endif
#endif
