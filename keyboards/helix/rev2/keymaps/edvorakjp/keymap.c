#include QMK_KEYBOARD_H
#include "split_util.h"
#include "keymap_xrows.h"

// keymaps definitions are moved to keymap_Xrows.c.

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_keymap(layer_state_t state) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    switch (get_highest_layer(state)) {
        case L_EDVORAKJP_LOWER:
            rgblight_sethsv_noeeprom_red();
            break;
        case L_EDVORAKJP_RAISE:
            rgblight_sethsv_noeeprom_green();
            break;
        default:  //  for any other layers, or the default layer
            rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
            rgblight_sethsv_red();
            break;
    }
    return state;
}
#endif
