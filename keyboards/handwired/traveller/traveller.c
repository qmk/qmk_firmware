#include "quantum.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

#ifdef RGBLIGHT_ENABLE
    rgblight_init();
    rgblight_mode(1); // solid, no timer
    rgblight_setrgb(0,20,0);// dim green, happens to be same as _QW
#endif

    // Turn status LED on
    setPinOutput(C7);
    writePinHigh(C7);

    matrix_init_user();
}
