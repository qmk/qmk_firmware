#include QMK_KEYBOARD_H
#include "digitizer.h"
#include "math.h"


enum my_layers {
    _BASE
};


enum my_keycodes {
    MY_FUZZ = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    RESET,  DZ_TIP1, DZ_BAR1, DZ_BAR2, MY_FUZZ,
    DZ_P_C, DZ_P_U0, DZ_P_U1, DZ_P_U2, DZ_P_U3
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    digitizer_t digitizer;
    switch (keycode) {
        case MY_FUZZ:
            if (record->event.pressed) {
                // Set mouse to the top of the screen, 50% of the way across
                digitizer = digitizer_fuzz_xy(DIG_REL2ABS_X(0.5), 0);
                // Press the tip switch (usually treated as left mouse button)
                digitizer.buttons |= DIG_TIP_PRIMARY;
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
                return false;
            } else {
                // Release the tip switch
                digitizer = digitizer_get_report();
                digitizer.buttons &= ~DIG_TIP_PRIMARY;
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
                return false;
            }
        default:
            return true;
    }
}
