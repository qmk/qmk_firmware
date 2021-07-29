#include QMK_KEYBOARD_H
#include "split_util.h"
#include "keymap_xrows.h"

// keymaps definitions are moved to keymap_Xrows.c.

#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_keymap(uint32_t state) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    switch (biton32(state)) {
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
