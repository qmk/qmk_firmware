#pragma once

#if defined(__AVR__)
#    include <avr/pgmspace.h>
#else
#    define PROGMEM
#    define pgm_read_byte(p) *((unsigned char*)(p))
#    define pgm_read_word(p) *((uint16_t*)(p))
#    define pgm_read_dword(p) *((uint32_t*)(p))
#endif
