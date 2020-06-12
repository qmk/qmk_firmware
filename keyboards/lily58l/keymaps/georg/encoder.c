#include QMK_KEYBOARD_H
#include "keymap.h"

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    HSV hsv;
    switch (get_highest_layer(layer_state)) {
        case _RAISE:  // brightness control
            if (get_mods() & MOD_MASK_SHIFT) {
                if (clockwise)
                    rgblight_increase_hue();
                else
                    rgblight_decrease_hue();
            } else {
                hsv = rgblight_get_hsv();
                int16_t v = hsv.v + (clockwise ? 1 : -1) * RGBLIGHT_VAL_STEP;
                if (v <= 0) {
                    rgblight_disable();
                    v = 0;
                } else if (!rgblight_is_enabled())
                    rgblight_enable();

                rgblight_sethsv(hsv.h, hsv.s, v);
            }
            break;
        default:  // Volume control
            if (clockwise) 
                tap_code(KC_VOLU);
            else
                tap_code(KC_VOLD);
            break;
}
    }
#endif