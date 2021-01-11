#include "mattly.h"

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

void set_lights_default(void) {
    #ifdef RGBLIGHT_ENABLE
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgblight_sethsv_noeeprom(HSV_CAPS);
        } else {
            rgblight_sethsv_noeeprom(HSV_DEFAULT);
        }
    #endif
}

void layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
        case _QWERTY:
            set_lights_default();
            break;
        case _SYMBOL:
            rgblight_sethsv_noeeprom(HSV_SYMBOL);
            break;
        case _NAVNUM:
            rgblight_sethsv_noeeprom(HSV_NAVNUM);
            break;
        case _FUNCT:
            rgblight_sethsv_noeeprom(HSV_FUNCT);
            break;
    }
#endif
}


layer_state_t layer_state_set_user (layer_state_t state) {
  state = update_tri_layer_state(state, _SYMBOL, _NAVNUM, _FUNCT);
  layer_state_set_rgb(state);
  return layer_state_set_keymap (state);
}

void on_reset(void) {
    #ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_noeeprom(HSV_RESET);
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            #ifdef RGBLIGHT_ENABLE
            set_lights_default();
            #endif
            return true;
        case RESET:
            on_reset();
            return true;
        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    set_lights_default();
#endif
}
