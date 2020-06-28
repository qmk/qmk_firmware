#include QMK_KEYBOARD_H
#include "keymap.h"

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGBLIGHT_ENABLE
    HSV hsv;
    bool shifted = get_mods() & MOD_MASK_SHIFT;  // precision steps
#endif
    switch (get_highest_layer(layer_state)) {
        case _RAISE:  // brightness control
#ifdef RGBLIGHT_ENABLE
            hsv = rgblight_get_hsv();
            if (get_mods() & MOD_MASK_CTRL) {
                hsv.h = hsv.h + (clockwise ? 1 : -1) * (shifted ? 1 : RGBLIGHT_HUE_STEP);
            } else {
                int16_t v = hsv.v + (clockwise ? 1 : -1) * (shifted ? 1 : RGBLIGHT_VAL_STEP);
                if (v <= 0) {
                    rgblight_disable();
                    v = 0;
                } else if (!rgblight_is_enabled())
                    rgblight_enable();
                hsv.v = v;
            } 
            rgblight_sethsv(hsv.h, hsv.s, hsv.v);
            break;
#endif
        case _LOWER:
            tap_code(clockwise ? KC_BRIU : KC_BRID);
            break;
        default:  // Volume control
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
}
    }
#endif