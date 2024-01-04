#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}},
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}},
    /* Right hand, matrix positions */
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}},
};
#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif
#endif

void eeconfig_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(3);
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB by default
    rgblight_sethsv(0, 255, 255);  // Set default HSV - red hue, full saturation, full brightness
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default
#endif
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
