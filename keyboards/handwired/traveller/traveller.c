#include "traveller.h"

void matrix_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
        rgblight_init();
        rgblight_mode(1); // solid, no timer
        rgblight_setrgb(0,20,0);// dim green, happens to be same as _QW
#endif

// Turn status LED on
        DDRC |= (1<<7);
        PORTC |= (1<<7);
}
