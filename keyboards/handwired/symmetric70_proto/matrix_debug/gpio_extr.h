#pragma once
// clang-format off

#if defined(__AVR__)
#    define readPort(port) PINx_ADDRESS(port)
typedef uint8_t     port_data_t;
#else
#    define readPort(qmk_pin) palReadPort(PAL_PORT(qmk_pin))
typedef uint16_t     port_data_t;
#endif
