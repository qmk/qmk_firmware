#pragma once

#if defined(RGB_MATRIX_ENABLE)
#    include "rgb_matrix.h"
#elif defined(RGBLIGHT_ENABLE)
#    if !defined(__AVR__)
#        define PROGMEM
#    endif
#    include "rgblight.h"
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_increase_flags(void);
void rgb_matrix_decrease_flags(void);
#endif

void rgb_reset(void);
