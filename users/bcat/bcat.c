#include "bcat.h"

#if defined(RGBLIGHT_ENABLE)
/* Adjust RGB static hue ranges for shorter gradients than default. */
const uint8_t RGBLED_GRADIENT_RANGES[] PROGMEM = {255, 127, 63, 31, 15};
#endif

static int8_t alt_tab_layer = -1;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        /* Alt+Tab that holds Alt until current layer is released: */
        case MC_ALTT:
            if (record->event.pressed) {
                if (alt_tab_layer < 0) {
                    alt_tab_layer = layer_switch_get_layer(record->event.key);
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        default:
            return true;
    }
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_keymap(state);
    if (alt_tab_layer >= 0 && !layer_state_cmp(state, alt_tab_layer)) {
        unregister_code(KC_LALT);
        alt_tab_layer = -1;
    }
    return state;
}
